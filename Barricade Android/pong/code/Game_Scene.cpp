/*
 * GAME SCENE
 * Copyright © 2018+ Ángel Rodríguez Ballesteros
 *
 * Distributed under the Boost Software License, version  1.0
 * See documents/LICENSE.TXT or www.boost.org/LICENSE_1_0.txt
 *
 * angel.rodriguez@esne.edu
 */

#include "Game_Scene.hpp"
#include "Menu_Scene.hpp"


#include <cstdlib>
#include <basics/Canvas>
#include <basics/Director>

using namespace basics;
using namespace std;

namespace example
{
    // ---------------------------------------------------------------------------------------------
    // ID y ruta de las texturas que se deben cargar para esta escena. La textura con el mensaje de
    // carga está la primera para poder dibujarla cuanto antes:

    Game_Scene::Texture_Data Game_Scene::textures_data[] =
    {





        { ID(loading),    "game-scene/loading.png"        },

        { ID(cuadradomorado), "game-scene/cubo_morado.png"      },
        { ID(cuadradoazul), "game-scene/cubo_azul.png"      },
        { ID(jugadormorao), "game-scene/jugador_morado.png"      },
        { ID(jugadorazul), "game-scene/jugadorazul.png"      },

        { ID(cuadricula), "game-scene/escenario.png"      },

        { ID(pausa),      "game-scene/pausa.png"      },
        { ID(resumeImg),      "game-scene/resume.png"      },
        { ID(menuImg),      "game-scene/menu.png"      },

        { ID(victoriaAzul),      "game-scene/victoriaAzul.png"      },
        { ID(victoriaMorada),      "game-scene/victoriaMorada.png"      },
        { ID(empate),      "game-scene/empate.png"      },



    };

    // Pâra determinar el número de items en el array textures_data, se divide el tamaño en bytes
    // del array completo entre el tamaño en bytes de un item:

    unsigned Game_Scene::textures_count = sizeof(textures_data) / sizeof(Texture_Data);

    // ---------------------------------------------------------------------------------------------
    // Definiciones de los atributos estáticos de la clase:



    // ---------------------------------------------------------------------------------------------

    Game_Scene::Game_Scene()
    {
        // Se establece la resolución virtual (independiente de la resolución virtual del dispositivo).
        // En este caso no se hace ajuste de aspect ratio, por lo que puede haber distorsión cuando
        // el aspect ratio real de la pantalla del dispositivo es distinto.

        canvas_width  = 1280;
        canvas_height =  720;


        //creo 2 jugadores
        meh;
        tonto;


        // Se inicia la semilla del generador de números aleatorios:

        srand (unsigned(time(nullptr)));


        // Se inicializan otros atributos:

        initialize ();
    }

    // ---------------------------------------------------------------------------------------------
    // Algunos atributos se inicializan en este método en lugar de hacerlo en el constructor porque
    // este método puede ser llamado más veces para restablecer el estado de la escena y el constructor
    // solo se invoca una vez.

    bool Game_Scene::initialize ()
    {
        state     = LOADING;
        suspended = true;
        gameplay  = UNINITIALIZED;

        //inicializo su velocidad a 0 a la espera de que empieze la partida
          meh.setSpeed(0,0);
        tonto.setSpeed(0,0);





        return true;
    }
    // ---------------------------------------------------------------------------------------------
   void Game_Scene::pantallaVictoria(int caso)

    {
        victoria=true;
        movimiento= false;
        paused= true;
        gameplay=PAUSED;

        meh.setSpeed(0,0);
        tonto.setSpeed(0,0);
        timer.reset();



        //dependiendo de quien ha ganado enseño una imagen
        /** caso 1: Azul gana
         * caso 2: Morado gana
         * caso 3:Empate
         */

            switch (caso) {
                case 1:{
                    Sprite_Handle Bluevictory (new Sprite( textures[ID(victoriaAzul)].get ()  ));
                    Bluevictory->set_anchor   (CENTER);
                    Bluevictory->set_position ({ canvas_width / 2.f, canvas_height / 2.f + 50 });
                    sprites.push_back(Bluevictory);

                    break;}

                case 2:
                {
                    Sprite_Handle PurpleVictory (new Sprite( textures[ID(victoriaMorada)].get ()  ));
                    PurpleVictory->set_anchor   (CENTER);
                    PurpleVictory->set_position ({ canvas_width / 2.f, canvas_height / 2.f + 50 });
                    sprites.push_back(PurpleVictory);

                    break;}
                case 3:{
                    Sprite_Handle Draw (new Sprite( textures[ID(empate)].get ()  ));
                    Draw->set_anchor   (CENTER);
                    Draw->set_position ({ canvas_width / 2.f, canvas_height / 2.f + 50 });
                    sprites.push_back(Draw);

                    break;}




            }














    }





    // ---------------------------------------------------------------------------------------------

    void Game_Scene::suspend ()
    {
        suspended = true;               // Se marca que la escena ha pasado a primer plano
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::resume ()
    {

        //Vuelvo a ponerle la velocidad a la que tenia antes del pause en memoria

        meh.setSpeed(meh.getMemorySpeedX(),meh.getMemorySpeedY());
        tonto.setSpeed(tonto.getMemorySpeedX(),tonto.getMemorySpeedY());


       //Activo el movimiento
        movimiento= true;
        paused= false;
        gameplay=PLAYING;
        suspended = false;              // Se marca que la escena ha pasado a segundo plano
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::handle (Event & event)
    {
        if (state == RUNNING)               // Se descartan los eventos cuando la escena está LOADING
        {
            if (gameplay == WAITING_TO_START)
            {
                start_playing ();           // Se empieza a jugar cuando el usuario toca la pantalla por primera vez
            }
            else switch (event.id)
            {
                case ID(touch-started):

                    //Si alguien ha ganado y se toca la pantalla se reinicia

                      if(victoria==true)  director.run_scene (shared_ptr< Scene >(new Game_Scene));

                case ID(touch-moved):
                {
                    //si hacemos click en pausa
                   if ( *event[ID(x)].as< var::Float > () < 178 &&  *event[ID(y)].as< var::Float > () >  670 && not paused  ) {
                       movimiento=false;
                       pausar();}


                       //si hacemos click en menu estando pausados
                    else if (*event[ID(x)].as< var::Float > () >580 && *event[ID(x)].as< var::Float > () < 700
                             && *event[ID(y)].as< var::Float > () >  360 && *event[ID(y)].as< var::Float > () <  420 && paused ){

                       director.run_scene (shared_ptr< Scene >(new Menu_Scene));
                   }
                     //si hacemos click en resume estando pausados
                   else if (*event[ID(x)].as< var::Float > () > 560 && *event[ID(x)].as< var::Float > () < 720
                            && *event[ID(y)].as< var::Float > () <  360 && *event[ID(y)].as< var::Float > () >  300 && paused ){

                       sprites.pop_back();
                       sprites.pop_back();
                       resume();
                   }

                       //establece la direccion del movimiento para los dos jugadores

                  else  if (movimiento){
                       meh.setDirecion(*event[ID(x)].as< var::Float > (),*event[ID(y)].as< var::Float > (),2);
                       tonto.setDirecion(*event[ID(x)].as< var::Float > (),*event[ID(y)].as< var::Float > (),3);

                   movimiento= false;
                   }


                    break;
                }

                case ID(touch-ended):       // El usuario deja de tocar la pantalla
                {
                    //reinicia la capacidad de cambiar de direccion
                 movimiento= true;
                    break;
                }
            }
        }
    }

    /*Pausa la partida y guarda las velocidades*/

    void Game_Scene::pausar(){
        movimiento= false;
        paused= true;
        gameplay=PAUSED;
       meh.setMemorySpeed(meh.getSpeedX(),meh.getSpeedY());
        tonto.setMemorySpeed(tonto.getSpeedX(),tonto.getSpeedY());
        meh.setSpeed(0,0);
        tonto.setSpeed(0,0);

        Sprite_Handle botonMenu (new Sprite( textures[ID(menuImg)].get ()  ));
        botonMenu->set_anchor   (CENTER);
        botonMenu->set_position ({ canvas_width / 2.f, canvas_height / 2.f + 50 });

        Sprite_Handle botonResume (new Sprite( textures[ID(resumeImg)].get ()   ));
        botonResume->set_anchor   (CENTER);
        botonResume->set_position ({ canvas_width / 2.f, canvas_height / 2.f -50});


        sprites.push_back (   botonMenu);
        sprites.push_back (   botonResume);


    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::update (float time)
    {
        if (!suspended) switch (state)
        {
            case LOADING: load_textures  ();     break;
            case RUNNING: run_simulation (time); break;
            case ERROR:   break;
        }
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::render (Context & context)
    {
        if (!suspended)
        {
            // El canvas se puede haber creado previamente, en cuyo caso solo hay que pedirlo:

            Canvas * canvas = context->get_renderer< Canvas > (ID(canvas));

            // Si no se ha creado previamente, hay que crearlo una vez:

            if (!canvas)
            {
                 canvas = Canvas::create (ID(canvas), context, {{ canvas_width, canvas_height }});
            }

            // Si el canvas se ha podido obtener o crear, se puede dibujar con él:

            if (canvas)
            {
                canvas->clear ();

                switch (state)
                {
                    case LOADING: render_loading   (*canvas); break;
                    case RUNNING: render_playfield (*canvas); break;
                    case ERROR:   break;
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------------------
    // En este método solo se carga una textura por fotograma para poder pausar la carga si el
    // juego pasa a segundo plano inesperadamente. Otro aspecto interesante es que la carga no
    // comienza hasta que la escena se inicia para así tener la posibilidad de mostrar al usuario
    // que la carga está en curso en lugar de tener una pantalla en negro que no responde durante
    // un tiempo.

    void Game_Scene::load_textures ()
    {
        if (textures.size () < textures_count)          // Si quedan texturas por cargar...
        {
            // Las texturas se cargan y se suben al contexto gráfico, por lo que es necesario disponer
            // de uno:

            Graphics_Context::Accessor context = director.lock_graphics_context ();

            if (context)
            {
                // Se carga la siguiente textura (textures.size() indica cuántas llevamos cargadas):

                Texture_Data   & texture_data = textures_data[textures.size ()];
                Texture_Handle & texture      = textures[texture_data.id] = Texture_2D::create (texture_data.id, context, texture_data.path);

                // Se comprueba si la textura se ha podido cargar correctamente:

                if (texture) context->add (texture); else state = ERROR;

                // Cuando se han terminado de cargar todas las texturas se pueden crear los sprites que
                // las usarán e iniciar el juego:
            }
        }
        else
        if (timer.get_elapsed_seconds () > 1.f)         // Si las texturas se han cargado muy rápido
        {                                               // se espera un segundo desde el inicio de
            create_sprites ();                          // la carga antes de pasar al juego para que
            restart_game   ();                          // el mensaje de carga no aparezca y desaparezca
                                                        // demasiado rápido.
            state = RUNNING;
        }
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::create_sprites ()
    {
        // Se crean y configuran los sprites del fondo:
        Sprite_Handle cuad(new Sprite( textures[ID(cuadricula)].get ()              ));


        Sprite_Handle JugadorMorado (new Sprite( textures[ID(jugadormorao)].get ()  ));
        Sprite_Handle JugadorAzul (new Sprite( textures[ID(jugadorazul)].get ()     ));
        Sprite_Handle botonpausa (new Sprite( textures[ID(pausa)].get ()     ));






        JugadorMorado->set_anchor   (TOP | LEFT);
        JugadorMorado->set_position ({ 0, canvas_height / 2.f  });

        JugadorAzul->set_anchor   (TOP | LEFT);
        JugadorAzul->set_position ({ canvas_width-20, canvas_height / 2.f  });

        botonpausa->set_anchor(TOP | LEFT );
        botonpausa->set_position ({ 0, canvas_height  });


        cuad->set_anchor   (CENTER);
        cuad->set_position ({ canvas_width / 2.f, canvas_height / 2.f });


        sprites.push_back (   cuad);





        sprites.push_back (   JugadorMorado);
        sprites.push_back (   JugadorAzul);

        sprites.push_back(  botonpausa  );




        playerAzu = JugadorAzul.get();
        playerMora = JugadorMorado.get();
        escenario = cuad.get();
        pausa = botonpausa.get();

        meh.setSprite(playerAzu);
        tonto.setSprite(playerMora);



    }

    // ---------------------------------------------------------------------------------------------
    // Juando el juego se inicia por primera vez o cuando se reinicia porque un jugador pierde, se
    // llama a este método para restablecer la posición y velocidad de los sprites:

    void Game_Scene::restart_game()
    {
     

        gameplay = WAITING_TO_START;
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::start_playing ()
    {

        //Les pongo velocidad inicial a los jugadores y empieza la partida


        meh.setSpeed(-1,0);
        tonto.setSpeed(1,0);






        gameplay = PLAYING;
    }

    // ---------------------------------------------------------------------------------------------

    void Game_Scene::run_simulation (float time)
    {
        // Se actualiza el estado de todos los sprites:

        if(gameplay==PLAYING && not paused){


        if(timer.get_elapsed_seconds()>0.1) {
            for (auto &sprite : sprites) {
                sprite->update(0.1);
            }



//Añado un cubo cada tick

            Sprite_Handle cuadradoAzul2(new Sprite(textures[ID(cuadradoazul)].get()));
            cuadradoAzul2->set_anchor(TOP|LEFT);
            cuadradoAzul2->set_position({playerAzu->get_position_x(), playerAzu->get_position_y()});
            sprites.push_back(cuadradoAzul2);

            Sprite_Handle cuadradomorado(new Sprite(textures[ID(cuadradomorado)].get()));
            cuadradomorado->set_anchor(TOP|LEFT);
            cuadradomorado->set_position({playerMora->get_position_x(), playerMora->get_position_y()});
            sprites.push_back(cuadradomorado);

//Muevo los jugadores
            meh.movimiento();
            tonto.movimiento();




//Compruebo las colisiones con el mapa
              meh.colisionParedes( );
              tonto.colisionParedes( );  ;


//Compruebo colisiones con los sprites
            for (auto &sprite : sprites) {
                if (sprite.get() != escenario && sprite.get() != playerMora && sprite.get() != playerAzu && sprite.get() != pausa  ) {
                    if( playerAzu->intersects(*sprite.get()) ) meh.setMuerto(true);
                }
            };

            for (auto &sprite : sprites) {
                if (sprite.get() != escenario && sprite.get() != playerMora && sprite.get() != playerAzu && sprite.get() != pausa  ) {
                    if(  playerMora->intersects(*sprite.get()))tonto.setMuerto(true);
                }
            };

//Victoria si procede
            if (meh.estamuerto() && tonto.estamuerto()) pantallaVictoria(3);
            else if (meh.estamuerto() && !tonto.estamuerto()) pantallaVictoria(2);
            else if (!meh.estamuerto() && tonto.estamuerto()) pantallaVictoria(1);











            timer.reset();
        }

    }
    }






    // ---------------------------------------------------------------------------------------------

    void Game_Scene::render_loading (Canvas & canvas)
    {
        Texture_2D * loading_texture = textures[ID(loading)].get ();

        if (loading_texture)
        {
            canvas.fill_rectangle
            (
                { canvas_width * .5f, canvas_height * .5f },
                { loading_texture->get_width (), loading_texture->get_height () },
                  loading_texture
            );
        }
    }

    // ---------------------------------------------------------------------------------------------
    // Simplemente se dibujan todos los sprites que conforman la escena.

    void Game_Scene::render_playfield (Canvas & canvas)
    {
        for (auto & sprite : sprites)
        {
            sprite->render (canvas);
        }
    }

}
