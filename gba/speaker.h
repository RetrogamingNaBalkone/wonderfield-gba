#pragma once
/* Frequency is passed through the original PC PIT divisor before synthesis. */
void speaker_init(void);
void speaker_tone(unsigned hz,unsigned milliseconds);
void speaker_queue_tone(unsigned hz,unsigned milliseconds);
void speaker_effect(unsigned effect,unsigned random_seed);
void speaker_enable(int on);
void speaker_irq(unsigned flags);
