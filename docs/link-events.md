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
and the event's full-state FNV check remain enabled.

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

Between events the host exchanges a compact input/keepalive packet roughly once
per six VBlanks. It contains HEADER, START flags and input: three logical words,
normally 24 hardware transfers under the existing acknowledged CRC transport.
The client notices the next low-byte request in the serial IRQ state and otherwise
continues its local presentation. The snapshot and its hash are omitted from a
keepalive. Clients redraw only for local visual changes or a received event.

A/B/SELECT/START edge bits accompany held keys so a second press is distinguishable
when release happened between polls. The host still accepts gameplay input only
from the current player's console. Repeated phases back off while a peer is
rendering; the minimum 4096-cycle turnaround remains in place.

Build fingerprint and creator/join roles are session checks. Lobby names are sent
on change; avatar/edit flags share one word. An admitted late lobby participant
resets the snapshot baseline on all peers. A reset/join during a running match is
rejected. Leaving/reopening the connection resets all session/event caches.

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
