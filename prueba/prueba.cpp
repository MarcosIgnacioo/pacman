// lo terminamos la siguiente semana no copium

#include <iostream>
#include <ctime>
#include <cmath>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
using namespace std;
int main()
{
    ALLEGRO_DISPLAY* display; // Esto sirve para crear la pantalla 
    ALLEGRO_FONT* font; // Esto sirve para cargar  la fuente de letronas
    ALLEGRO_EVENT_QUEUE* queue; // Esto sirve para crear una cola de eventos agregar mas cosas luego
    ALLEGRO_TIMER* timer; // Esto sirve para crear el timer es decir tiempito wu
    ALLEGRO_BITMAP* bitmap = NULL; // Esto sirve para crear el bitmap q es donde se va a guardar la imagen se le pone el null porq luego lo cargas
    
    al_init();
    display = al_create_display(640, 480);
    queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60); // limita fps
    font = al_load_ttf_font("CourierPrime-Regular.ttf", 64, 0);

    al_install_keyboard();
    al_install_mouse();
    al_register_event_source(queue, al_get_keyboard_event_source());//Registra todas las entradas del teclado
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display)); // Registra todos los eventos que ocurran con la ventana * se le tiene que indicar el nombre de la misma
    al_register_event_source(queue, al_get_timer_event_source(timer));                                                             //al_init_font_addon();
    al_init_ttf_addon();

    al_init_image_addon();
    bitmap = al_load_bitmap("elmcara.jpg");
    assert(bitmap != NULL);
    
    bool running = true;
    float x = 0, y = 0;
    int movimiento = 0;
    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    al_start_timer(timer);
    while (running) // Esto es el ciclo por el cual el juego va a estar funcionando
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event); 
        
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // Se crea un evento en el que se detecta la tecla que se quiera y pues se termina el progrmama porque se cambia el valor del ciclo
        {
            running = false;
        }
        // mouse basicamente mueve el cuadrito a donde esta el mouse va a servir para debuggear asi q lo guardamos
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            x = event.mouse.x;
            y = event.mouse.y;
        }
        if (event.type == ALLEGRO_EVENT_TIMER )
        {
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));//al_clear_to_color(al_map_rgb(23, 45, 34)); // Colorea todo de negro (El fondo)
            al_draw_bitmap(bitmap, x, y,0);//al_draw_text(font, al_map_rgb(0, 0, 0), 0, 0, 0, "Pac-man"); // Colorea la fuente (Blanco) usan codigos rgb asi que a buscarlos
            al_flip_display();// Ordena a la grafica mostrar todo ponerlo en un if hace que solo se actualice cada segundo creo deja checo el video de nuevo jajajaj tengo retraso por el amor de dios por que tengo que estaar queriendome morir ahora mismo tengo 18 putos a;os como 40 por delante si es que soy pendejo y no tengo ni ganas de ver el final de este a;o  pero si es algo neutro o bueno pues me conformo si es bueno q curado rng enjoyer siiiii estooy bien estupidop
        }
        

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            x = y = 0;
            al_set_mouse_xy(display, 0, 0);
        }

        ALLEGRO_KEYBOARD_STATE keyState;
        al_get_keyboard_state(&keyState);

        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) // Parte del movimiento: Lo q hice para que se moviese de manera infinita fue asignarle a cada tecla un cambio de variable t pues cada vez que se presioona una tecla esta cambia por lo que la direccion tambien, esta medio pocho porq creo que se puede mejorar peroo pues asi jala, si lo mejoras ahi m avisas ah si y
        {
            movimiento = 1; //  la manera en la q funciona el movimiento infinito es porque el aumento de movimiento ocurre 
                            //en un else puesto que al no estar ocurriendo los ifs (oprimiendo las teclas) 
                            //pues se sigue en esa direccion hasta que pues se cambie no se si me explique espero q si
        }
           
        
        else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
        {
            movimiento = 2; 
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
        {
            movimiento = 3;
            
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
        {
            movimiento = 4;
            
        }

        else // else magicon
        {
            if (movimiento == 1 && x < 625)
            {
                cout << x<< endl;
                x += 8;
            }
            else if (movimiento == 2 && x > 5)
            {
                cout << x << endl;
                x -= 8;    // las X y Y pues mueven las coordenadas del bitmap asi q dependiendo d la direccion se sumna o resta
            }                  // y la segunda condicional detecta q noo se haya pasado d los bordes d la pantalla asi q lo detiene ahi
                              // cuanto a q esto nos va a ocasionar pedos luego con las colisiones del laberinto
            else if (movimiento == 3 && y > 0)
            {
                cout << y << endl;
                y -= 8;
            }
            else if (movimiento == 4 && y < 465)
            {
                cout << y << endl;
                y += 8;
            }
        }
    }
    al_destroy_display(display); // Sirve para chingarte la ventana
    al_destroy_font(font); // Sirve para chingarte las letras
    al_uninstall_keyboard(); // desinstalar el teclaadoo buena practica para ahorrrar  memoria
    al_destroy_timer(timer); //TODAS DESTRUYEN JKHSADFHJH
    al_destroy_bitmap(bitmap);
    return 0;
}
