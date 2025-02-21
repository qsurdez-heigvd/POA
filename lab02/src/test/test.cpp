
/**
 * @file Implementation of the different tests we make on the classes we coded
 * 
 * @author Jallon Sarah
 * @author Surdez Quentin
*/

#include <gtest/gtest.h>
#include "src/ship/TIE/TIE.hpp"
#include "src/ship/cargo/Shuttle.hpp"
#include "src/ship/cargo/StarDreadnought.hpp"
#include "../squadron/Squadron.hpp"
#include "src/ship/TIE/TIEInterceptor.hpp"
#include "../utils/ostreamUtils.hpp"

TEST(ConstructorSquadron, defaultConstructor) {
   Squadron squadron("Squadron 1");
   ASSERT_EQ(squadron.empty(), true);
}

TEST(ConstrucorSquadron, copyConstructor) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   TIEInterceptor interceptor1;
   squadron.addShip(interceptor1);
   Squadron squadron2(squadron);
   std::cout << squadron << std::endl;
   std::cout << squadron2 << std::endl;
   ASSERT_EQ(squadron.empty(), false);
   ASSERT_EQ(squadron2.empty(), false);
}

TEST(ConstructorSquadron, moveConstructor) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   TIEInterceptor interceptor1;
   squadron.addShip(interceptor1);
   Squadron squadron2(std::move(squadron));
   std::cout << squadron << std::endl;
   std::cout << squadron2 << std::endl;
   ASSERT_EQ(squadron.empty(), true);
   ASSERT_EQ(squadron2.empty(), false);
}

TEST(Assignments, CopyAssignment) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   TIEInterceptor interceptor1;
   squadron.addShip(interceptor1);
   Squadron squadron2 = squadron;
   std::cout << squadron << std::endl;
   std::cout << squadron2 << std::endl;
   ASSERT_EQ(squadron.empty(), false);
   ASSERT_EQ(squadron2.empty(), false);
}

TEST(Assignments, MoveAssignment) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   TIEInterceptor interceptor1;
   squadron.addShip(interceptor1);
   Squadron squadron2 = std::move(squadron);
   std::cout << squadron << std::endl;
   std::cout << squadron2 << std::endl;
   ASSERT_EQ(squadron.empty(), true);
   ASSERT_EQ(squadron2.empty(), false);
}

TEST(Operations, AddShipToSelf) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   TIEInterceptor interceptor1;
   squadron.addShip(interceptor1);
   std::cout << squadron << std::endl;
   ASSERT_EQ(squadron.empty(), false);
}

TEST(Operations, AddShipCopy) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   Squadron squadron1 = squadron.addShipCopy(interceptor);
   std::cout << squadron1 << std::endl;
   ASSERT_EQ(squadron.empty(), true);
   ASSERT_EQ(squadron1.empty(), false);
}

TEST(Operations, DeleteShip) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   std::cout << squadron << std::endl;
   squadron.deleteShip(interceptor);
   std::cout << squadron << std::endl;
   ASSERT_EQ(squadron.empty(), true);
}

TEST(Operations, DeleteShipCopy) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron.addShip(interceptor);
   std::cout << squadron << std::endl;
   Squadron squadron1 = squadron.deleteShipCopy(interceptor);
   std::cout << squadron1 << std::endl;
   ASSERT_EQ(squadron.empty(), false);
   ASSERT_EQ(squadron1.empty(), true);
}

TEST(Operations, plusEqual) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   std::cout << squadron << std::endl;
   ASSERT_EQ(squadron.empty(), false);
}

TEST(Operations, minusEqual) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   std::cout << squadron << std::endl;
   squadron -= interceptor;
   std::cout << squadron << std::endl;
   ASSERT_EQ(squadron.empty(), true);
}

TEST(Operations, plus) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   Squadron squadron1 = squadron + interceptor;
   std::cout << squadron1 << std::endl;
   ASSERT_EQ(squadron.empty(), true);
   ASSERT_EQ(squadron1.empty(), false);
}

TEST(Operations, minus) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   std::cout << squadron << std::endl;
   Squadron squadron1 = squadron - interceptor;
   std::cout << squadron1 << std::endl;
   ASSERT_EQ(squadron.empty(), false);
   ASSERT_EQ(squadron1.empty(), true);
}

TEST(Getter, getShip) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   std::cout << squadron.get(0) << std::endl;
}

TEST(Getter, getShipOutOfBounds) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   EXPECT_THROW(
             {
               try {
                   std::cout << squadron.get(1) << std::endl;
               } catch (std::out_of_range &re) {
                   EXPECT_STREQ("Index out of range", re.what());
                   throw;
               }
             }, std::out_of_range);
}

TEST(Consumption, TotalConsumption) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   Shuttle shuttle(23.4);
   squadron += shuttle;
   StarDreadnought star(34.5);
   squadron += star;
   std::cout << squadron << std::endl;
   ASSERT_FLOAT_EQ(squadron.fuelConsumption(squadron.getWeight(), squadron.getMaximumSpeed()), 186796.56);
}

TEST(Consumption, TotalConsumptionIfEmpty) {
   Squadron squadron("Squadron 1");
   EXPECT_THROW(
             {
               try {
                   std::cout << squadron.fuelConsumption(squadron.getWeight(), squadron.getMaximumSpeed()) << std::endl;
               } catch (std::runtime_error &re) {
                   EXPECT_STREQ("Squadron is empty", re.what());
                   throw;
               }
             }, std::runtime_error);
}

TEST(Chief, setChief) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   squadron.setChief(interceptor);
   std::cout << squadron << std::endl;
}

TEST(Chief, setChiefIfAlreadyChief) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   Shuttle shuttle(23.4);
   squadron += interceptor;
   squadron.setChief(interceptor);
   std::cout << squadron << std::endl;
   squadron.setChief(shuttle);
   std::cout << squadron << std::endl;
}

TEST(Chief, removeChief) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   squadron.setChief(interceptor);
   std::cout << squadron << std::endl;
   squadron.removeChief();
   std::cout << squadron << std::endl;
}

TEST(Chief, removeChiefTwice) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   squadron.setChief(interceptor);
   std::cout << squadron << std::endl;
   squadron.removeChief();
   std::cout << squadron << std::endl;
   squadron.removeChief();
   std::cout << squadron << std::endl;
}

TEST(Others, maximumSpeed) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   Shuttle shuttle(23.4);
   squadron += shuttle;
   StarDreadnought star(34.5);
   squadron += star;
   std::cout << squadron << std::endl;
   ASSERT_FLOAT_EQ(squadron.getMaximumSpeed(), 40.0);
}

TEST(Others, totalWeight) {
   Squadron squadron("Squadron 1");
   TIEInterceptor interceptor;
   squadron += interceptor;
   Shuttle shuttle(23.4);
   squadron += shuttle;
   std::cout << squadron << std::endl;
   ASSERT_FLOAT_EQ(squadron.getWeight(), 388.39999);
}

TEST(Others, empty) {
   Squadron squadron("Squadron 1");
   ASSERT_EQ(squadron.empty(), true);
   TIE tie;
   squadron += tie;
   ASSERT_EQ(squadron.empty(), false);
}

int main(int argc, char **argv) {
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}

