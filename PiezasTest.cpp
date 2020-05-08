/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, simpleDropPieces)
{
	Piezas game;
	//First move should return X
	EXPECT_EQ(game.dropPiece(0), X);
	//Second move should return O
	EXPECT_EQ(game.dropPiece(1), O);
}

TEST(PiezasTest, dropPiecesErroring)
{
	Piezas game;

	//Fill a column
	EXPECT_EQ(game.dropPiece(0), X);
	EXPECT_EQ(game.dropPiece(0), O);
	EXPECT_EQ(game.dropPiece(0), X);

	//Checking to make sure filling a full column returns blank
	ASSERT_EQ(game.dropPiece(0), Blank);
	//second assertion for coverage of Blank for both player turns
	ASSERT_EQ(game.dropPiece(0), Blank);

	//testing an out of bounds dropPiece
	ASSERT_EQ(game.dropPiece(4), Invalid);
	//second assertion for coverage of Invalid for both player turns
	ASSERT_EQ(game.dropPiece(4), Invalid);
}

TEST(PiezasTest, resetBoard)
{
	Piezas game;

	//Fill the board with a arbitrary Piece
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 4; j++)
			game.dropPiece(j);

	//Now that the board is filled let's test that it actually is
	EXPECT_EQ(game.dropPiece(0), Blank);
	EXPECT_EQ(game.dropPiece(1), Blank);
	EXPECT_EQ(game.dropPiece(2), Blank);
	EXPECT_EQ(game.dropPiece(3), Blank);
	
	//Run reset
	game.reset();
	ASSERT_NE(game.dropPiece(0), Blank);
}