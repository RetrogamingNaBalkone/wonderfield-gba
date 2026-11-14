# Cable events and local presentation

The host alone executes rules, draws game RNG, selects turns, awards points and
changes rounds. A client never calls `stop_spin`, `complete_reveal`,
`begin_turn`, `new_round` or payout/departure handlers on its own.

## Publication boundary

`link_semantic_key()` observes rule state plus a presentation event revision.
`set_mode()` and `say()` advance that revision. Cursor/answer/choice, scores,
match state, intro phrase, gift page and payout completion also cause publication.
Clock ticks, RNG cursor, spin phases/sectors, helper coordinates/stops/revealed
cells, mouth poses and individual banknotes do not.

An event carries a checked delta of the authoritative state and the parameters
needed to start/resume its presentation. The receiving wire baseline remains
separate from locally animated `game`, `scene` and `cash`; applying the next delta
never uses client-mutated poses as its base. Word CRC/retry, commit acknowledgments
and each snapshot's full-state FNV check remain enabled.

| Presentation | Event parameters | Locally produced work | Host-only completion |
| --- | --- | --- | --- |
| Wheel | Start sector, target, step count and slowdown | Half-steps, sectors, timing, tones | Award/penalty and next mode |
| Helper | Revealed cells, target cells, initial position, reaction delay | Walking, stops, cell opening | Score and next turn/round |
| Host speech | Template IDs/arguments, speech seed/timing | Text formatting, mouth poses | Next dialogue/game phase |
| Introduction | Phrase/participant and start time | Bounce and speech | Next participant/phrase |
| Credits | Start time | Scrolling | Next round |
| Money | Amount, initial seed and start time | Banknotes and their sounds | Skip/final payout/departure |

The host and guests use the same wheel/helper/cash step routines. Guests stop at
the final pose until an authoritative event arrives. Wheel/helper timers catch
up after a delayed frame. Event delivery time is excluded from the presentation
clock, and received timers are rebased to each console's VBlank clock.

Messages use ROM-relative template IDs, valid only with the identical build
fingerprint. Dynamic turn, sector, offer and AI-letter/position lines carry their
arguments; player names refer to the synchronized roster. No RAM pointer or
per-frame formatted text is sent.

## Steady traffic and input

Between events the SIO parent exchanges a compact input/keepalive packet roughly once
per two VBlanks. It contains HEADER, START flags and input: three logical words,
normally 24 hardware transfers under the existing acknowledged CRC transport.
When a child hosts, one additional word relays the selected player's input.
The host announces the input owner in its request, so the cable parent never
selects input using an older copy of the turn state.
The client notices the next low-byte request in the serial IRQ state and otherwise
continues its local presentation. The snapshot and its hash are omitted from a
keepalive. Clients redraw only for local visual changes or a received event.

A/B/SELECT/START edge bits accompany held keys so a second press is distinguishable
when release happened between polls. The host still accepts gameplay input only
from the current player's console. VBlank captures presses in a separate ordered
queue; the input word samples that queue immediately before transmission, including
taps received while waiting for earlier words. A held button whose edge is still
queued cannot overtake an earlier direction or execute twice.
Repeated phases back off while a peer is
rendering; the minimum 4096-cycle turnaround remains in place.

Cursor/choice changes in TURN, LETTER, SOLVE and PLUS use one compact publication
word when every other semantic field is unchanged. Its tag, mode and player are
validated, and the authority checks the relayed value against its own word.
The normal CRC/commit transport delivers the same assignment to every peer's
previously verified snapshot. Both wire baselines advance together; navigation
does not send a full snapshot/hash or rebase presentation clocks. All other events
use the normal snapshot delta and full-state hash.

The active guest can preview one pending cursor move in TURN, LETTER or SOLVE.
The preview changes only the rendered cursor/choice; it never selects a letter,
changes the synchronized Game or executes rules. The next authoritative navigation,
mode or player change clears it. A direction followed quickly by A still executes
in order on the host. Spectators cannot preview another player's navigation.

The build fingerprint is checked when establishing a session. The first accepted
creation request elects the application host independently of the cable parent;
simultaneous requests tie by port and later requests cannot replace that host.
With a child hosting, each published event word is first collected by the parent
and then relayed to all peers. Both legs retain CRC/commit checks. Lobby metadata
is likewise collected and delivered to the elected authority. No per-pose events
are added by relaying. Lobby snapshots are requested only when rules, membership,
names, avatars or editing flags change; local keyboard cursor movement does not
request one. Names are sent on change; avatar/edit flags share one word. Unchanged
name/avatar screens are not redrawn while a peer awaits the next request.
Name edits repaint their text and changed keys; navigation on the game keyboard
repaints only the old and new keys when the rest of the view is unchanged.
An admitted late lobby participant
resets the snapshot baseline on all peers. A reset/join during a running match is
rejected. Leaving/reopening the connection resets all session/event caches.
An existing lobby child also abandons its old alternating phase when a returning
parent sends the bootstrap word, then establishes a fresh checked transport while
keeping its profile and lobby role.

Contiguous event delta runs share an index/length. Sparse changes retain the
previous index/value encoding, with monotonic-index and bounds checks on receive.

## Limits and verification

This remains synchronous GBA SIO during packet delivery; it is not a fully
asynchronous network stack. An emulator's own network synchronization can still
add latency to a transfer. The measured improvements and fault-injection results
are from mGBA, not Pizza Boy Advance or physical GBA hardware.

Reproduce local animation assertions with:

```
MGBA_BUILD=work/mgba-build python3 scripts/test-link.py --native --scenario 0 --animations
MGBA_BUILD=work/mgba-build python3 scripts/test-link.py --scenario 0 --animations --irq-delay 60000
MGBA_BUILD=work/mgba-build python3 scripts/test-link.py --native --scenario 0 --benchmark
```

The animation test observes independent ROM instances: zero new presentation
events while wheel/helper/cash poses advance, matching targets/letters/scores,
owner-only skips, local message text matching host text, local credits/mouth
progress and disconnect detection. It does not implement the animations itself.

The any-port host build's results, ROM SHA-256, native gameplay/menu logs,
animation assertions, benchmark baseline and test limitations are recorded in
[`verification/link-any-host-tests.json`](verification/link-any-host-tests.json).
The referenced fault reports keep every injected scenario and its output.
Benchmark `updates` counts authority main-loop iterations, not rendered FPS;
compare `transfers` over the fixed 600-VBlank interval for wire traffic.

Input latency samples and the corresponding ROM hashes are in
[`verification/link-input-latency-tests.json`](verification/link-input-latency-tests.json).
`test-link-roles.py --native --scenario 1 --consoles 2 --graphics 1 --latency`
measures short taps at eight polling offsets, owner feedback, host acceptance and
cursor convergence, then checks that a quick direction/A pair inserts exactly the
expected letter once. `owner_frames` observes cursor/preview state;
`visible_frames` checks the old and new key's highlight pixels in the displayed
VRAM page. Neither metric includes an emulator frontend's display buffering or
network transport outside mGBA's emulated cable. The latency test also forces a
full redraw and compares the entire displayed page byte for byte against each
incrementally rendered name/game keyboard.
