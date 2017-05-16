//#ifndef SHAPE_H
//#define SHAPE_H

//#include "block.h"
//#include "typeshape.h"
//#include "direction.h"

//namespace mikoli{

///*!
// * \brief The Shape class
// *
// * It is an abstract class which allows to define a general form and its methods.
// * \ref _typeShape The type of a form.
// */
//class Shape{
//private:
//    /*!
//     * \brief _typeShape
//     * The type of a form.
//     */
//    TypeShape _typeShape;

//protected:
//    /*!
//     * \brief Shape constructor with a type parameter needed.
//     * This constructor will initialize the typeShape attribute.
//     * \ref _typeShape The type of the shape
//     */
//  //  Shape(TypeShape typeShape);

//    /*!
//     * \brief Shape constructor without parameters.
//     * This constructor will initialize the typeShape attribute.
//     */
//    Shape();

//    /*!
//     * \brief Shape inline destructor.
//     * Deallocate the memory that was previously reserved for the Shape.
//     */
//    virtual ~Shape() {};

//    /*!
//     * \brief getType() Recover the type of the figure
//     * \return The figure's type.
//     */
//    TypeShape getType();

//    //Others methods

//    /*!
//     * \brief move Virtual method: Makes it possible to move a figure to the left, right or down.
//     * \param direction The direction in which the figure should be moved.
//     */
//    virtual void move(Direction direction) = 0;

//    /*!
//     * \brief rotate Virtual method: Makes it possible to rotate a figure to the left or to the right.
//     * \param direction The direction in which the figure should rotate.
//     */
//    virtual void rotate(Direction direction) = 0;

//    /*!
//     * \brief newPosition Virtual method: Makes it possible to displace a figure by
//     * modifying the location of its central point.
//     * \param position The new position of the figures's central point.
//     */
//    virtual void newPosition(Position position) = 0;

//};

//}

//#endif // SHAPE_H
