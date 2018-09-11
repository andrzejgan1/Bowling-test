#include <gtest/gtest.h>
#include "Bowling.hpp"

struct BowlingTests : public ::testing::Test
{
    //GIVEN
    Bowling bowling;
};

TEST_F(BowlingTests, check_if_inicial_NumberOfLanes_is_zero)
{
    //THEN
    ASSERT_EQ(0, bowling.getNumberOfLanes());
}

TEST_F(BowlingTests, add_1_lane_expect_NumberOfLanes_1)
{
    //WHEN
    Lane lane;
    bowling.addLane(lane);
    //THEN
    ASSERT_EQ(1, bowling.getNumberOfLanes());
}

TEST_F(BowlingTests, add_1_lane_with_1_game_Adam_X_2_expect_NumberOfLanes_1_name_game_Adam_score_14)
{
    //WHEN
    Game game("Adam:X|2");
    Lane lane;
    lane.addGame(game);
    bowling.addLane(lane);
    //THEN
    ASSERT_EQ(1, bowling.getNumberOfLanes());
    ASSERT_EQ("Adam", bowling.getLane(0).getGame(0).getName());
    ASSERT_EQ(14, bowling.getLane(0).getGame(0).score());
    ASSERT_EQ("game in progress", bowling.getLane(0).getStatusLane());
}

TEST_F(BowlingTests, when_directory_to_read_no_existe_expect_in_stdout_message_Wrong_directory)
{
    //WHEN
    testing::internal::CaptureStdout();
    bowling.readDirectory("asdfsa");
    std::string output = testing::internal::GetCapturedStdout();
    //THEN
    ASSERT_EQ("Wrong directory\n", output);
}

TEST_F(BowlingTests, when_read_directory_data_tests_expect_numberOfLanes_3_in_lane_2_in_game_2_expect_name_Sandra_score_16)
{
    //WHEN
    bowling.readDirectory("../tests/data_tests");
    //THEN
    ASSERT_EQ(3, bowling.getNumberOfLanes());
    ASSERT_EQ("Sandra", bowling.getLane(1).getGame(1).getName());
    ASSERT_EQ(16, bowling.getLane(1).getGame(1).score());
}

TEST_F(BowlingTests, when_read_empty_file_in_lane_3_expect_NumberOfGames_0_and_status_no_games)
{
    //WHEN
    bowling.readDirectory("../tests/data_tests");
    //THEN
    ASSERT_EQ(0, bowling.getLane(2).getNumberOfGames());
    ASSERT_EQ("No games", bowling.getLane(2).getStatusLane());
}

TEST_F(BowlingTests, when_read_directory_and_get_lane_out_of_range_expect_throw)
{
    //WHEN
    bowling.readDirectory("../tests/data_tests");
    //THEN
    ASSERT_THROW(bowling.getLane(48), std::out_of_range);
}

TEST_F(BowlingTests, add_1_lane_with_1_game_in_progress_expect_status_game_in_progress)
{
    //WHEN
    Game game("Adam:11|22|33|44|4");
    Lane lane;
    lane.addGame(game);
    bowling.addLane(lane);
    //THEN
    ASSERT_EQ(1, bowling.getNumberOfLanes());
    ASSERT_EQ("Adam", bowling.getLane(0).getGame(0).getName());
    ASSERT_EQ("game in progress", bowling.getLane(0).getGame(0).getStatus());
}

TEST_F(BowlingTests, add_1_lane_with_1_game_finished_expect_status_game_finished)
{
    //WHEN
    Game game("Adam:11|22|33|44|55|11|22|33|44|55");
    Lane lane;
    lane.addGame(game);
    bowling.addLane(lane);
    //THEN
    ASSERT_EQ(1, bowling.getNumberOfLanes());
    ASSERT_EQ("Adam", bowling.getLane(0).getGame(0).getName());
    ASSERT_EQ("Game finished", bowling.getLane(0).getGame(0).getStatus());
}

TEST_F(BowlingTests, add_1_lane_with_1_game_with_extra_roll_expect_status_game_in_progress)
{
    //WHEN
    Game game("Adam:11|22|33|44|55|11|22|33|44|5/");
    Lane lane;
    lane.addGame(game);
    bowling.addLane(lane);
    //THEN
    ASSERT_EQ(1, bowling.getNumberOfLanes());
    ASSERT_EQ("Adam", bowling.getLane(0).getGame(0).getName());
    ASSERT_EQ("game in progress", bowling.getLane(0).getGame(0).getStatus());
}
