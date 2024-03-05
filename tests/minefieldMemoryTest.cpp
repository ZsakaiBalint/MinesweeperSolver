#include "pch.h"
#include "../src/minefieldMemory.cpp"

TEST(MinefieldMemory, markAsMineFree) {
	Beginner beginner;
	MinefieldMemory memory(beginner);
	EXPECT_FALSE(memory.isOpened({ 3,2 }));
	memory.markAsMinefree({ { 3,2 } });
	EXPECT_TRUE(memory.isOpened({ 3,2 }));
	EXPECT_TRUE(memory.isMinefree({ 3,2 }));
}

TEST(MinefieldMemory, markAsMine) {
	Beginner beginner;
	MinefieldMemory memory(beginner);
	EXPECT_FALSE(memory.isOpened({ 3,2 }));
	EXPECT_FALSE(memory.isOpened({ 4,2 }));
	memory.markAsMine({ { 3,2 },{ 4,2 } });
	EXPECT_TRUE(memory.isOpened({ 3,2 }));
	EXPECT_TRUE(memory.isMine({ 3,2 }));
	EXPECT_TRUE(memory.isOpened({ 4,2 }));
	EXPECT_TRUE(memory.isMine({ 4,2 }));
}