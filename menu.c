/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: pipi
 *
 * Created on August 16, 2020, 3:01 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_primitives.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>// NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
#include <allegro5/allegro_image.h> //NO OLVIDAR INCLUIR ALLEGRO_IMAGE EN LINKER
#include <allegro5/allegro_color.h> // NO OLVIDAR AGREGAR EN EL LINKER DEL PROYECTO
//#include <stdbool.h>



#define FPS    60.0
#define SCREEN_W  800
#define SCREEN_H  530

//DEFINO COORDENADAS DE LOS BOTONES
#define MOUSE_IN_PLAY ((ev.mouse.x>244)&(ev.mouse.x<539)&(ev.mouse.y>245)&(ev.mouse.y<286))
#define MOUSE_IN_EXIT ((ev.mouse.x>335)&(ev.mouse.x<462)&(ev.mouse.y>308)&(ev.mouse.y<345))
#define MOUSE_IN_HIGH_SCORE ((ev.mouse.x>307)&(ev.mouse.x<465)&(ev.mouse.y>390)&(ev.mouse.y<412))


/*
 * 
 */
int main(int argc, char** argv) {
    


    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE * event_queue = NULL;
    ALLEGRO_BITMAP *buffer = NULL;
    ALLEGRO_BITMAP *fondo_menu = NULL;
    ALLEGRO_BITMAP *fondo_play = NULL;
    ALLEGRO_BITMAP *fondo_exit = NULL;
    ALLEGRO_BITMAP *fondo_high_score = NULL;
    ALLEGRO_TIMER *timer = NULL;

   

    bool redraw = false;
    bool do_exit = false;
    

    //CARGO ALLEGRO Y LO QUE VOY A USAR (MOUSE, IMAGENES, SONIDO...).
    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_mouse()) {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
      if (!al_init_image_addon()) { // ADDON necesario para manejo(no olvidar el freno de mano) de imagenes 
        fprintf(stderr, "failed to initialize image addon !\n");
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        return -1;
    }


    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(fondo_menu);
        al_destroy_bitmap(fondo_play);
        al_destroy_bitmap(fondo_exit);
        al_destroy_bitmap(fondo_high_score);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }
    
    //CARGO LAS IMÁGENES.

    fondo_menu = al_load_bitmap("fondo_menu.bmp");
    if (!fondo_menu) {
        fprintf(stderr, "failed to load fondo_menu !\n");
        return 0;
    }
        fondo_play = al_load_bitmap("fondo_play.bmp");
    if (!fondo_play) {
        fprintf(stderr, "failed to load fondo_play !\n");
        return 0;
    }
         fondo_exit = al_load_bitmap("fondo_exit.bmp");
    if (!fondo_exit) {
        fprintf(stderr, "failed to load fondo_exit !\n");
        return 0;
    }
         fondo_high_score = al_load_bitmap("fondo_high_score.bmp");
    if (!fondo_high_score) {
        fprintf(stderr, "failed to load fondo_high_score !\n");
        return 0;
    }    
         
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_draw_bitmap(fondo_menu, 0, 0, 0);
    al_flip_display();
    al_start_timer(timer);

    while (!do_exit) 
    {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
        {
            if (ev.type == ALLEGRO_EVENT_TIMER) // por que tenemos un timer para redibujar?
                redraw = true;

            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)//Si se cierra el display cerrar
                do_exit = true;

            else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
            {
                if(MOUSE_IN_PLAY)
                {
                    al_draw_bitmap(fondo_play, 0, 0, 0);
                    al_flip_display();
                }
                else if(MOUSE_IN_EXIT)
                {
                    al_draw_bitmap(fondo_exit, 0, 0, 0);
                    al_flip_display();
                } 
                else if(MOUSE_IN_HIGH_SCORE)
                {
                    al_draw_bitmap(fondo_high_score, 0, 0, 0);
                    al_flip_display();
                }    
                else
                {
                    al_draw_bitmap(fondo_menu, 0, 0, 0);
                    al_flip_display();
                }    

            }
            else if ( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP&&(MOUSE_IN_EXIT))
            {
                do_exit= true;
                
            }    
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
           
            
        }

    }

    al_destroy_bitmap(fondo_menu);
    al_destroy_bitmap(fondo_play);
    al_destroy_bitmap(fondo_exit);
    al_destroy_bitmap(fondo_high_score);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}




