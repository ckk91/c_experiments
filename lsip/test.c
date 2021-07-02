#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

int main(int argc, char const *argv[])
{
    al_init();
    al_install_keyboard();

    ALLEGRO_DISPLAY* disp = al_create_display(320,200);
    //
    return 0;
}
// allegro vivace tutorial 