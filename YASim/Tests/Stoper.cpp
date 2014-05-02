#include "gtest/gtest.h"
#include "YASim/Util/Stoper.h"
#include <thread>

using YASim::Util::Stoper;

TEST(Stoper, IsStopEqualToStart)
{
	Stoper st;
	st.stop();
	std::chrono::milliseconds noTimeM(0);
	long long noTimeI(0);
	EXPECT_EQ(noTimeM, st.getMiliseconds());
	EXPECT_EQ(noTimeI, st.getMiliseconds().count());
}

TEST(Stoper, IsStopGreaterThanStart)
{
	std::chrono::milliseconds mili_3(3);
	Stoper st;
	std::this_thread::sleep_for(mili_3);
	st.stop();
	EXPECT_EQ(mili_3, st.getMiliseconds());
	EXPECT_EQ(mili_3.count(), st.getMiliseconds().count());
}

TEST(Stoper, IsGetDurationSameAsGetMiliseconds)
{
	Stoper st;
	st.stop();
	std::chrono::milliseconds noTime(0);
	EXPECT_EQ(noTime, st.getMiliseconds());
	EXPECT_EQ(st.getDuration<std::chrono::milliseconds>(), st.getMiliseconds());
	EXPECT_EQ(st.getDuration<std::chrono::milliseconds>().count(), st.getMiliseconds().count());
}

