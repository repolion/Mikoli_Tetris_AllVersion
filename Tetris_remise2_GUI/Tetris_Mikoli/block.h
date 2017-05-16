#ifndef BLOCK_H
#define BLOCK_H

#include "position.h"
#include "color.h"
#include "direction.h"
#include <QColor>

namespace mikoli{

/*!
 * \brief The Block class
 *
 * This class will be used for building blocks that are part of a figure.
 * A standard figure is composed with 4 blocks.
 * \ref _position the position of the block in the board.
 * \ref _color the color of the block.
 */
class Block{
private:
    //Private Attributes
    /*!
     * \brief _position
     * The position of the block in the board.
     */
    Position _position;

    /*!
     * \brief _color
     * The color of the block in the board.
     */
    Color _color;

public:
    //Constructor / destructor
    /*!
     * \brief Block's Constructor without parameters.
     * This constructor will use the default constructor of Position for _position
     * and set the color to red.
     */
    Block();

    /*!
     * \brief Block's Constructor with parameters.
     * \param x The value for the horizontal axis of the block.
     * \param y The value for the vertical axis of the block.
     * \param color The color of the block.
     */
    Block(int x, int y,Color color);

    /*!
     * \brief Block's destructor.
     */
    ~Block();

    //Getters
    /*!
     * \brief getPosition
     * \return return The position of the block.
     */
    Position getPosition() const;

    /*!
     * \brief getColor
     * \return The Qcolor of the block.
     */
    QColor getColor();

    //Setter
    /*!
     * \brief setPosition
     * \param x The new value for the horizontal axis.
     * \param y The new value for the ordinate axis.
     */
    void setPosition(int x, int y);

    // Others
    void move(Direction direction);
};

}

#endif // BLOCK_H
