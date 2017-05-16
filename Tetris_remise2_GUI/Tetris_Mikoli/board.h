#ifndef BOARD_H
#define BOARD_H

#include "figure.h"
#include "tetrisexception.h"
#include "soundplayer.h"
#include <list>
#include <math.h>
#include <unordered_map>
#include <iostream>


namespace mikoli{

/*!
 * \brief The Board class
 *
 * This class is used to represent a fictive board in which the user will play.
 * Here will stand the blocks and the current figure of the player.
 * A "fictive board" because it's not really a board.
 * It is a list of Block. This list contains only the blocks placed in the graphical board.
 * There are methods that allow to handle the moves of the current figure,
 * to rotate the current figure and the suppression of lines, the reorganization of the blocks in the "board".
 *
 * \ref _listBlocks The list of the blocks inside the board.
 * \ref _width The width of the board.
 * \ref _height The height of the board.
 * \ref _entryPoint The position where the current figure appears when she arrives in the board.
 */
class Board{
private:
    //Private Attributes
    /*!
     * \brief _listBlocks
     * This attribute composes the "board". It contains all the blocks that can be placed in the graphical board.
     * Used to know if a position is free or if it's possible to move/rotate/put a figure.
     */
    std::list<Block> _listBlocks;

    /*!
     * \brief height
     * This attribute is the logical height of the board.
     */
    int _height;

    /*!
     * \brief width
     * This attribute is the logical witdh of the board.
     */
    int _width;

    /*!
     * \brief _entryPoint
     * This attribute represent the entry point of each figure in the board.
     * Every time
     */
    Position _entryPoint;

    /*!
     * \brief _rotationSound
     * The sound when we rotate a figure.
     */
    SoundPlayer * _rotationSound;

    /*!
     * \brief _rotationFailSound
     * The sound when we can't rotate a figure.
     */
    SoundPlayer * _rotationFailSound;

public:

    //Constructors
    /*!
     * \brief Board's constructor without parameters.
     * This constructor uses the constructor with parameters by setting the height to 20 and the width to 10.
     */
    Board();

    /*!
     * \brief Board's constructor with parameters.
     * \param height The height of the board.
     * \param width The width of the board.
     */
    Board(int height, int width);

    // Destructor inline
    /*!
     * \brief ~Board's inline destructor.
     */
    inline ~Board(){}

    //Getter

    /*!
     * \brief getBlocks
     * \return The list of the blocks in the board.
     */
    std::list<Block> getBlocks() const ;

    //Others methods

    /*!
     * \brief addFigure
     * \param cF The figure to add in the board.
     * Add the current figure to the board's list of blocks.
     */
    void addFigure(Figure & cF);

    /*!
     * \brief canGoLower
     * \param cF The current figure to test.
     * \return True if the figure can go once down, false otherwise.
     */
    bool canGoLower(Figure & cF);

    /*!
     * \brief validationHeight
     * This method check if the number received is >= 10.
     * \param nb The number to validate.
     * \return The number if he's >= 10, an exception otherwise.
     * \throw TetrisException if nb < 10.
     */
    int validationHeight(int nb);

    /*!
     * \brief validationWidth
     * This method check if the number received is >= 5.
     * \param nb The number to validate.
     * \return The number if he's >= 5, an exception otherwise.
     * \throw TetrisException if nb < 5.
     */
    int validationWidth(int nb);

    /*!
     * \brief move
     * This method uses canMove() to check if it's possible to move
     * the figure in this direction, and if so, will actually move the figure
     * by calling her method move().
     *
     * If itsn't possible to move the figure, the method does nothing.
     * \param cF The current figure.
     * \param direction The direction into move the figure.
     */
    void move(Figure & cF, Direction direction);

    /*!
     * \brief rotate
     * \param cF The current figure to rotate
     * \param direction The direction we want to rotate
     */
    void rotate(Figure & cF, Direction direction);

    /*!
     * \brief canMove
     * This method check if the current figure can move in the direction wished.
     * To do this, she calculates the new positions of the current figure and then
     * check if theses positions are available in the board. So, she compares theses positions
     * with the positions of the blocks in _listBlocks.
     * \param cF The current figure.
     * \param direction The direction we want to move.
     * \return true if the positions are available, false otherwise.
     */
    bool canMove(Figure cF, Direction direction);

    /*!
     * \brief canRotate
     * This method check if the current figure can rotate in the direction wished.
     * To do this, she calculates the new positions of the current figure and then
     * check if theses positions are available in the board. So, she compares theses positions
     * with the positions of the blocks in _listBlocks.
     * \param cF The current figure.
     * \param direction The direction we want to move.
     * \return true if the positions are available, false otherwise.
     */
    bool canRotate(Figure cF, Direction direction);

    /*!
     * \brief canPut
     * This method check if the position of the _entryPoint is available.
     * To do this, she calculates the positions the current figure need and check
     * if theses positions are available at the _entryPoint.
     * \param cF The figure we want to put in the board.
     * \return true if the positions are available, false otherwise.
     */
    bool canPut(Figure cF);

    /*!
     * \brief areBlocksAvailable
     * This method check is the new positions of the current figure are
     * available in the board.
     * \param cF The current figure
     * \return true if the positions are available, false otherwise.
     */
    bool areBlocksAvailable(Figure cF);

    /*!
     * \brief checkLines
     * This method check if there are lines in the board to delete.
     * It checks each lines of the board and for each x, check in the _listBlocks
     * if a block has this position.It calculates the number of blocks for each line
     * and if there are as much blocks as the width of the board, it adds the y
     * in a List to send to removeLines().
     * \return The list with all the lines to delete. If there isn't any lines to delete,
     * this list is empty.
     */
    int checkLines();

    /*!
     * \brief removeLines
     * This method receives a list of all the y in the board to delete and then, will just delete them.
     * \param line The line where all the blocks will be removed from the board's list.
     */
    void removeLine(int line);

    /*!
     * \brief reorganize
     * This method will get down all the blocks in the middle of the board
     * after a suppression of lines. She's called after isFragmented() in the case she returns true.
     */
    void reorganize(int line);

    /*!
     * \brief entryPoint
     * This method calculate the position of the _entryPoint.
     * To do this, it calculates it from the width and the height of the board.
     * \return The position of the _entryPoint.
     */
    Position entryPoint();

    /*!
     * \brief fall
     * This method will get the current figure straight to the bottom of the board.
     * It is called after the player pressed a certain button.
     */
    int fall(Figure & cF);


    /*!
     * \brief setBlockDown
     * \param bl The block to move
     * This method is used in reorganize().
     * It changes the position of the block to y - 1.
     */
    void setBlockDown(Block & bl);

    /*!
     * \brief reset
     *  This method cleans the board's list of blocks.
     */
    void reset();

    /*!
     * \brief getBoardSize
     * \return A pair with two integers, the width and height of the board.
     */
    std::pair<int,int> getBoardSize();

};

}

#endif // BOARD_H
