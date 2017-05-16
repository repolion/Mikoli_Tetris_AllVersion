#ifndef POSITION_H
#define POSITION_H

#include <string>

namespace mikoli{

/*!
 * \brief The Position class
 *
 * This class will be used to determinate the Block's Position in the board.
 * \ref _x The abscissa.
 * \ref _y The ordinate.
 */
class Position{
private:
    //Private Attributes
    /*!
     * \brief _x
     * X can't be negative, so it's minimal value is 0.
     */
    int _x;

    /*!
     * \brief _y
     * Y can't be negative, so it's minimal value is 0.
     */
    int _y;

public:
    //Constructor / Destructor
    /*!
     * \brief Position's constructor without parameters.
     * This constructor will set the _x attribute
     * and Y to 0.
     */
    Position();

    /*!
     * \brief Position's constructor with 2 parameters.
     * \param x the value for horizontal axis.
     * \param y the value for vertical axis.
     */
    Position(int x, int y);

    /*!
     * \brief Position's destructor.
     */
    ~Position();

    //Getters
    /*!
     * \brief getX
     * \return The value of _x.
     */
    int getX();

    /*!
     * \brief getY
     * \return The value of _y.
     */
    int getY();

    //Setters
    /*!
     * \brief setX
     * \param x The new value for _x.
     */
    void setX(int x);

    /*!
     * \brief setY
     * \param y The new value for _y.
     */
    void setY(int y);

    // Other method
    /*!
     * \brief isSame
     * \param position The position to compare to.
     * \return true if The position is the same, false otherwise.
     */
    bool isSame(Position position);
};

}
#endif // POSITION_H
