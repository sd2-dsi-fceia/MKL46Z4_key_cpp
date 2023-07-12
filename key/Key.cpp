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

/*==================[inclusions]=============================================*/

#include "Key.h"
#include <algorithm>

/*==================[macros and definitions]=================================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*==================[constructor and destroyer]==============================*/
Key::Key(board_swId_enum swId)
:swId(swId), estSw(ESPERANDO_ACTIVACION), eventSW(false)
{
    Key::getAllKeys().push_back(this);
}

Key::~Key()
{
    std::vector<Key*>& allKeys = getAllKeys();
    allKeys.erase(std::remove(allKeys.begin(), allKeys.end(), this), allKeys.end());
}

/*==================[static methods]=========================================*/

void Key::clearAllEv()
{
    std::vector<Key*>& allKeys = getAllKeys();
    for (Key* key : allKeys)
    {
        key->clearEv();
    }
}

void Key::periodicTask1Ms()
{
    std::vector<Key*>& allKeys = getAllKeys();
    for (Key* key : allKeys)
    {
        key->task1Ms();
    }
}

/*==================[public methods]=========================================*/

void Key::clearEv()
{
    eventSW = false;
}

bool Key::getPressEv()
{
    bool ret = false;

    if (eventSW)
    {
        eventSW = 0;
        ret = true;
    }

    return ret;
}

/*==================[private methods]========================================*/

std::vector<Key*>& Key::getAllKeys()
{
    // Estructura de datos para almacenar todas las instancias de Key
    static std::vector<Key*> allKeys;
    return allKeys;
}

void Key::task1Ms(void)
{
    switch (estSw)
    {
        case ESPERANDO_ACTIVACION:
            if (board_getSw(swId))
            {
                eventSW = 1;
                estSw = ESPERANDO_DESACTIVACION;
            }
            break;

        case ESPERANDO_DESACTIVACION:
            if (!board_getSw(swId))
            {
                estSw = ESPERANDO_ACTIVACION;
            }
            break;

        default:
            estSw = ESPERANDO_ACTIVACION;
            break;
    }
}

/*==================[end of file]============================================*/
