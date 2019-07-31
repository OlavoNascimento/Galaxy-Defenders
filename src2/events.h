#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED


void key_pressed_down_event_dealing(ALLEGRO_EVENT *event);

void key_pressed_up_event_dealing(ALLEGRO_EVENT *event);

void timer_event_dealing(void);

void deal_with_events(ALLEGRO_EVENT *event);



#endif // EVENTS_H_INCLUDED
