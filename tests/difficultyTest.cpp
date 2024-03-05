#include "pch.h"
#include "../src/difficulty.cpp"

TEST(Difficulty, initialization) {
	Beginner b;
	Intermediate i;
	Expert e;

	EXPECT_EQ(8, b.getWidth() );
	EXPECT_EQ(8, b.getHeight() );
	EXPECT_EQ(10, b.getNumberOfMines() );

	EXPECT_EQ(16, i.getWidth());
	EXPECT_EQ(16, i.getHeight());
	EXPECT_EQ(40, i.getNumberOfMines());

	EXPECT_EQ(30, e.getWidth());
	EXPECT_EQ(16, e.getHeight());
	EXPECT_EQ(99, e.getNumberOfMines());

	EXPECT_EQ(b.toString(), "BEGINNER");
	EXPECT_EQ(i.toString(), "INTERMEDIATE");
	EXPECT_EQ(e.toString(), "EXPERT");
}