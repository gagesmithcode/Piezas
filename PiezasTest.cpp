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

	//testing an out of bounds dropPiece
	ASSERT_EQ(game.dropPiece(4), Invalid);
}