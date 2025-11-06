#pragma once

#include <cmath>
#include <float.h>

// Eli tässä siis tehtiin vain alias, normaalille liukuluvulle kun tarvitaan vain yksinkertaista tarkkuutta
// Huomiona : onko siis niin, että nämä operaatiot pitää myös kaikki uudelleenkirjoittaa eri tarkkuudella, vai hoidetaanko
// tämä jotenkin elegantimmin? Päivitetään kommenttia myöh.


namespace Impi {

	typedef float real;
#define real_sqrt sqrtf
#define real_pow powf
#define real_abs fabsf

#define real_sin sinf
#define real_cos cosf
#define real_exp expf
#define real_epsilon FLT_EPSILON
}
