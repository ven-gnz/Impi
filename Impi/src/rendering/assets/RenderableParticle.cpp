#include "rendering/assets/RenderableParticle.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Vector3.h"

/*
Perinnällä mennään, ehkä tähän löytyy joku toimivampi ratkaisu myöhemmin.

EDIT 6.10 : järkevämpi ratkaisu löytyi, se oli ulkoistaa piirtäminen scenelle jolla on referenssi shader ohjelmaan.
Ideana tutkia, saisiko partikkelien sijainnin integroinnin säikeistettyä tai rinnakkaistettua.
*/