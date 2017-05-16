#ifndef DIRECTION_H
#define DIRECTION_H

namespace mikoli{

/*!
 * \brief The Direction enum
 *
 * This enumeration is used in several methods, like move, rotate, etc.
 * It indicates the direction to move, or rotate, and according
 * the direction, the calculs and the new position are different.
 * There are only three directions because the game doesn't allow
 * the user to go up.
 */
enum class Direction{
    LEFT,RIGHT,DOWN
};

}

#endif // DIRECTION_H
