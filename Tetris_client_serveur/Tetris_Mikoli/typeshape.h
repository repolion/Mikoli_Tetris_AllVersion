#ifndef TYPESHAPE_H
#define TYPESHAPE_H

namespace mikoli{

/*!
 * \brief The TypeShape enum
 *
 * This enumeration is used to indicate what kind of form the figure is.
 * According to the form, the pivot point will have a precise place, and the others blocks
 * are calculated around this pivot point.
 * We also need to know what kind of form we treat in the move and rotate methods, for example.
 * Each form rotate and move differently and the calculs aren't the same.
 */
enum class TypeShape{

    I,O,T,J,L,Z,S,C

};

}

#endif // TYPESHAPE_H
