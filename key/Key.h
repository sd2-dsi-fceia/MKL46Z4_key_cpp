/* Copyright 2023, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2023, Gustavo Muro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef KEY_H_
#define KEY_H_

/*==================[inclusions]=============================================*/
#include <vector>
#include "SD2_board.h"

/*==================[macros and typedef]=====================================*/
typedef enum
{
    ESPERANDO_ACTIVACION = 0,
    ESPERANDO_DESACTIVACION,
}estSw_enum;

/*==================[external data declaration]==============================*/

/*==================[external functions definition]==========================*/

/*==================[class definition]=======================================*/
class Key
{
public:
/*==================[constructor and destroyer]==============================*/
    Key(board_swId_enum swId);
    ~Key();

/*==================[static methods]=========================================*/
    static void clearAllEv();
    static void periodicTask1Ms();

/*==================[public methods]=========================================*/
    void clearEv();
    bool getPressEv();

/*==================[private methods]========================================*/
private:
    static std::vector<Key*>& getAllKeys();
    void task1Ms();

/*==================[private attributes]====================================*/
    const board_swId_enum swId;
    estSw_enum estSw;
    bool eventSW;
};

#endif /* KEY_H_ */

/*==================[end of file]============================================*/
