#ifndef FIGURE_H
#define FIGURE_H

#include "block.h"
#include "tetrisexception.h"
#include <list>
#include <vector>
#include "typeshape.h"

namespace mikoli{
/*!
 * \brief The Figure class
 *
 * This class is used to construct a figure.
 * A figure is composed with 4 blocks and a center
 * point around which the figure can rotate.
 * \ref _Blocks An array of 4 blocks .
 * \ref _axePoint The point around which the figure can
 * rotate also used to put a figure in the board at a certain position.
 */
class Figure{

private:
    //Private Attributes
    /*!
     * \brief _Blocks
     * An array of 4 blocks which form the figure .
     */
    Block _Blocks[4];

    /*!
     * \brief _typeFigure
     * The type of the figure
     */
    TypeShape _typeFigure;

public:
    //Constructors

    /*!
     * \brief Figures constructor without parameters.
     * This constructor will use the constructor without parameters og
     * Position for initializing the attribute _position
     * and settings the _color attribute to red.
     */
    Figure();
    /*!
     * \brief Figures Constructor with parameters.
     * \param typeShape The type of the Figure.
     */
    Figure(TypeShape typeShape);

    //Destructor inline
    /*!
     * \brief Figures destructor.
     */
    ~Figure(){};

    //Getter

    /*!
     * \brief getPositions
     * \return return The list of positions which forms the figure.
     */

    std::vector<Position> getPositions();

    /*!
     * \brief getBlocks
     * \return return a list of Blocks which forms the figure.
     */
    std::vector<Block> getBlocks();

    /*!
     * \brief getTypeFigure
     * \return The type of the figure
     */
    TypeShape getTypeFigure();

    //Setter

    void setBlocks(std::vector<Block>);

    //Others methods

    /*!
     * \brief move Makes it possible to move a figure to the left, right or down.
     * \param direction The direction in which the figure should be moved.
     */
    void move(Direction direction);
    /*!
     * \brief rotate Makes it possible to rotate a figure to the left or to the right.
     * \param direction The direction in which the figure should rotate.
     */
    void rotate(Direction direction);
    /*!
     * \brief newPosition Makes it possible to displace a figure by
     * modifying the location of its central point.
     * \param position The new position of the figures's central point.
     */
    void newPosition(Position position);
};

}

#endif // FIGURE_H
