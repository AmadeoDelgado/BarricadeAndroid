

#include "Jugador.hpp"




using namespace basics;
using namespace std;

namespace example
{

    //SETS Y GETS BASICOS
    void jugador::setMuerto(bool muerto) {
        this->muerto=muerto;
    }

    bool jugador::estamuerto(){
        return  this->muerto;
    }


    void jugador::setSpeed(int x, int y) {
        this->SpeedX=x;
        this->SpeedY=y;
    }

    void jugador::setSprite(Sprite *imagen)
    {
       this->jugadorSpr=imagen;
    }

    void  jugador::setMemorySpeed(int x, int y)
    {

        MemorySpeedX=x;
        MemorySpeedY=y;
    }

    int jugador::getMemorySpeedX() { return this->MemorySpeedX;}
    int jugador::getMemorySpeedY(){ return this->MemorySpeedY;}



    int jugador::getSpeedX() {
        return this->SpeedX;
    }

    int jugador::getSpeedY(){
        return this->SpeedY;
    }



//DIRECCION MOVIMIENTO Y COLISIONES

    void jugador::setDirecion(float x, float y,int caso)
    {
        if(jugadorSpr != nullptr) {

            //1 vs ia, 2 lado derecho, 3 lado izquierdo pantalla

            switch (caso)

            { case 1:
                    if (this->SpeedX != 0 && (y > this->jugadorSpr->get_position_y()))
                        this->setSpeed(0, 1);
                    else if (this->SpeedX != 0 && (y < this->jugadorSpr->get_position_y()))
                        this->setSpeed(0, -1);

                    else if (this->SpeedY != 0 && (x < this->jugadorSpr->get_position_x()))
                        this->setSpeed(-1, 0);
                    else if (this->SpeedY != 0 && (x > this->jugadorSpr->get_position_x()))
                        this->setSpeed(1, 0);
                    break;

                case 2:

                    if (this->SpeedX != 0 && (y > 360) && (x>640))
                        this->setSpeed(0, 1);
                    else if (this->SpeedX != 0 && (y < 360) && (x>640))
                        this->setSpeed(0, -1);

                    else if (this->SpeedY != 0 && (x < 960) && (x > 640) )
                        this->setSpeed(-1, 0);
                    else if (this->SpeedY != 0 && (x > 960))
                        this->setSpeed(1, 0);

                    break;

                case 3:
                    if (this->SpeedX != 0 && (y > 360) && (x<640))
                        this->setSpeed(0, 1);
                    else if (this->SpeedX != 0 && (y < 360) && (x<640))
                        this->setSpeed(0, -1);

                    else if (this->SpeedY != 0 && (x < 320))
                        this->setSpeed(-1, 0);
                    else if (this->SpeedY != 0 && (x > 320) && (x < 640))
                        this->setSpeed(1, 0);
                    break;


            }





        }

    }


    void jugador::movimiento()
    {
        jugadorSpr->set_position_x(jugadorSpr->get_position_x() + (20*SpeedX));
        jugadorSpr->set_position_y(jugadorSpr->get_position_y() + (20*SpeedY));
    }

    void jugador::colisionParedes(){
        if (jugadorSpr!= nullptr)
           muerto= ( jugadorSpr->get_position_x() > 1260 || jugadorSpr->get_position_x()<0 || jugadorSpr->get_position_y()> 720 || jugadorSpr->get_position_y()< 20);





    }


}
