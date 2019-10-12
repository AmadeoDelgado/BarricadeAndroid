





    #include <basics/Canvas>
    #include <basics/Id>
    #include <basics/Scene>
    #include <basics/Texture_2D>
    #include <basics/Timer>
    #include "Sprite.hpp"



    namespace example {


        class jugador {

            typedef std::shared_ptr < Sprite     >     Sprite_Handle;
            typedef std::list< Sprite_Handle     >     Sprite_List;

        private:

           bool muerto=false;

            Sprite *jugadorSpr= nullptr;

            int SpeedX=-1;
            int SpeedY=0;

            int MemorySpeedX=0;
            int MemorySpeedY=0;





        public:
            /** Constructor por defecto */
            jugador ()= default;

            /** Sets y gets */
            void setMuerto(bool muerto);
            bool estamuerto();

            void setSpeed(int x,int y);
            void setSprite(Sprite *imagen);
            void setMemorySpeed(int x,int y);

            int getSpeedX();
            int getSpeedY();
            int getMemorySpeedX();
            int getMemorySpeedY();


             /** Establece el movimiento del jugador, los casos son 1 vs ia, 2 lado derecho, 3 lado izquierdo pantalla  */
            void setDirecion(float x, float y,int caso);

            /** Mueve el sprite */
            void movimiento();
             /** Revisa si se ha salido del mapa */
            void colisionParedes();






        };
    }


