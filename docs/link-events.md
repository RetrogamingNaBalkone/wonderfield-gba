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
never uses client-mutated poses as its base. Block CRC-16/retry, two-phase commit
and each snapshot's full-state FNV check remain enabled.

## Block transport

The cable parent clocks every transfer. A packet is a sequence of blocks; each
block exchanges up to 64 words from every console. Every GBA receives every
SIOMULTI slot, so a child also keeps and CRC-checks the other children's slots it
needs; its verdict covers them:

1. probes until every member answers `READY(kind, n)` (a probe repeats COMMIT for
   the last committed block, so a child that missed it catches up);
2. HEADER with a 2-bit sequence number, an attempt bit, the kind and `n`;
3. `n` data words in both directions, then each side's CRC-16 of its own words;
4. ASK, answered by each child's verdict on the parent's words (attempt and
   sequence included);
5. COMMIT if every member's verdict and CRC match, otherwise RETRY.

A child's serial IRQ answers from the block its main loop armed: a reply written
after transfer k is latched for transfer k+1, so a block costs n+4 transfers plus
probes, instead of 8 transfers per word. A child accepts only the kind and length
it armed and never infers a commit from other words, because payload seen out of
position may resemble framing. While blocks fail, the turnaround between transfers
doubles from 4096 up to 131072 cycles so a late serial IRQ still sees every
transfer; it halves after each success. Probes back off to 65536 cycles while a
child is still drawing.

A guest arms the next REQUEST block when its packet ends. Its IRQ answers that
block and then arms CONTROL itself (CONTROL carries no guest data), so a keepalive
completes while the guest's main loop renders. Only event packets wait for the
guest's main loop.

| Block | Parent sends | Children send | Purpose |
| --- | --- | --- | --- |
| REQUEST | request, input | request, input | roles, events, owner input |
| CONTROL | control word, owner input | — | decisions; input for a child host |
| BUILD | fingerprint | fingerprint | full packets only |
| LOBBY | status, name | status, name | lobby events |
| PUBLISH | authority words | authority words | navigation/length, delta chunks |
| HASH | snapshot hash | snapshot hash | end-to-end check |
| VERDICT | mismatch flag | — | commit or full resync |

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

Between events the SIO parent exchanges a keepalive packet every two VBlanks:
REQUEST and CONTROL, about 12 transfers plus probes. The owner's input travels in
REQUEST; the parent forwards it in CONTROL, which is how a host on a child port
receives it. The host announces the input owner in its request, so the cable
parent never selects input using an older copy of the turn state. The snapshot
and its hash are omitted from a keepalive. Clients redraw only for local visual
changes or a received event.

Presses are logical events produced on the owner's console. Its VBlank applies the
same autorepeat timing as local play (18 VBlanks, then every 5) and queues one key
per event; simultaneous presses queue directions before buttons. Consecutive
repeats of one direction coalesce up to four per event. The input word carries
held keys in bits 0-8, the event key index+1 in bits 10-13 and its count-1 in
bits 14-15. The authority queues received presses and applies one per main-loop
iteration; it never derives presses or autorepeat from held keys, which are only
sampled once per packet. Queued presses are dropped when the current player
changes. Held keys only gate START arming and cancellation. The host still accepts
gameplay input only from the current player's console.
`scripts/test-link-input.py` runs the production functions against local play for
taps, holds and every packet period/phase from 2 to 12 VBlanks.

Cursor/choice changes in TURN, LETTER, SOLVE and PLUS use one compact publication
word when every other semantic field is unchanged. Its tag, mode and player are
validated, and the authority checks the relayed value against its own word.
The normal block transport delivers the same assignment to every peer's
previously verified snapshot. Both wire baselines advance together; navigation
does not send a full snapshot/hash or rebase presentation clocks. All other events
use the normal snapshot delta and full-state hash.

The active guest can preview one pending cursor move in TURN, LETTER or SOLVE.
The preview changes only the rendered cursor/choice; it never selects a letter,
changes the synchronized Game or executes rules. The next authoritative navigation,
mode or player change clears it. A direction followed quickly by A still executes
in order on the host. Spectators cannot preview another player's navigation.

A transfer whose SIOCNT ERROR flag is set keeps its position in the block but fails
the block's check, so the block is repeated. Sixteen consecutive ERROR samples end
the session.

The build fingerprint is checked when establishing a session. The first accepted
creation request elects the application host independently of the cable parent;
simultaneous requests tie by port and later requests cannot replace that host.
With a child hosting, the parent takes each PUBLISH block from the host's slot,
and with three consoles the remaining child reads that slot itself in the same
block; the parent commits only after that child's verdict also covers it. In the
LOBBY block a host on a child port reads the other child's slot the same way.
No block is relayed. Lobby snapshots are requested only when rules, membership,
names, avatars or editing flags change; local keyboard cursor movement does not
request one. A lobby event sends every console's avatar/edit flags and name in one
LOBBY block. A submitted name is judged for conflicts only by a snapshot built
from it. Unchanged name/avatar screens are not redrawn while a peer awaits the next
request.
Name edits repaint their text and changed keys; navigation on the game keyboard
repaints only the old and new keys when the rest of the view is unchanged.
An admitted late lobby participant
resets the snapshot baseline on all peers. A reset/join during a running match is
rejected. Leaving/reopening the connection resets all session/event caches.
An existing lobby child also abandons its block state when a returning parent sends
the bootstrap word, then establishes a fresh transport while keeping its profile
and lobby role.

Snapshots are sent as a byte XOR delta against the verified wire baseline, in
PUBLISH blocks of up to 64 words. Each token combines a zero skip and a literal run
in one byte (four bits each); counts of 15 or more use 255-byte extensions. The
length word has bit 15 set and gives the byte length. Padding must be zero,
skips/literals must remain within the snapshot, and decoding must consume exactly
that snapshot. The full-state FNV check still precedes applying Game, messages or
rules.

The snapshot zeroes `game.frame` and `scene.last_redraw`: guests never read these
per-iteration counters, so they no longer enter every delta. `game.rng` stays
because guests use it for local wheel timing.

The wire scene/cash clock excludes accumulated packet pauses. Both deadlines and
the event clock subtract the same offset before serialization; the receiver adds
its local clock offset when applying the event. This preserves presentation ages
and wraparound while preventing each packet pause from changing every deadline in
the following delta.

## Limits and verification

The parent's main loop still drives every transfer, and event packets wait for the
guests' main loops; it is not a fully asynchronous network stack. An emulator's own network synchronization can still
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

Event delivery measurements are in
[`verification/link-event-delivery-tests.json`](verification/link-event-delivery-tests.json).
`test-link-roles.py --native --scenario 1 --consoles 2 --graphics 1 --event-latency`
times real A-button transitions into SOLVE, SPIN and the spin-result message.
It measures from the host mode change until all consoles have applied its mode and
presentation revision, then checks both decoded message lines against the host.
These are event application timings, before any additional frontend display delay.
`test-link-codec.py` tests the production codec extracted from `link.inc`, with
round trips, truncated/malformed streams, guard bytes, ASan and UBSan.

Состояние работ и план: [`link-roadmap.md`](link-roadmap.md).

## Snapshot recovery and current measurements

Request bit 7 asks for a full baseline without reopening the session. Both hash
halves are always exchanged; the cable parent then broadcasts a mismatch verdict.
A rejected working snapshot is rolled back to the last committed wire baseline,
without applying it to Game. Every peer requests a full snapshot in the next
packet. Full recovery disables the compact navigation path. Build mismatch and
malformed framing still fail closed.

With the block transport and IWRAM drawing primitives
(`verification/link-render-tests.json`, `verification/link-direct-slot-tests.json`)
event application takes 6–8 frames with
two consoles (17–24 before the block transport) and 7–9 with three (31–41),
where a child host now costs no more transfers than with two consoles;
keepalives run every two VBlanks and the host loop keeps 60 iterations per second.
The remaining time is the packet itself and about two frames of the host's own
scene drawing, which the event waits for. The roadmap's
two-frame target is not met. The November 15 audit is in
`verification/link-roadmap-audit.json`. The three-console animation fixture failure was traced to direct debugger writes
to choice during temporary render/navigation state restoration. The fixture now
uses actual LEFT input. Native two/three-console animation runs pass with hosts
on ports 0 and 1; see `verification/link-animation-fixture-audit.json` and
`verification/link-animation-fixtures-fixed.json`.
