#include "pch.h"
#include "CppUnitTest.h"
#include "mapping_r.h"
#include "shipment_r.h"
#include "truck_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unitTestsft
{

    /////////////////////////BLACK BOX //////////////////////////
    TEST_CLASS(BlackBoxValidateWeightTests)
    {
    public:
        // Test cases for validateWeight function
        TEST_METHOD(NegativeInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateWeight(-10.5f), L"Negative input should return invalid");
        }

        TEST_METHOD(ValidInput_ReturnsValid)
        {
            Assert::AreEqual(1, validateWeight(25.3f), L"Valid input should return valid");
        }

        TEST_METHOD(NullInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateWeight(NULL), L"Null input should return invalid");
        }

        TEST_METHOD(EmptyStringInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateWeight(0.0f), L"Empty string input should return invalid");
        }
    };

    TEST_CLASS(BlackBoxValidateSizeTests)
    {
    public:
        // Test cases for validateSize function
        TEST_METHOD(NegativeInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateSize(-15.8f), L"Negative input should return invalid");
        }

        TEST_METHOD(ValidInput_ReturnsValid)
        {
            Assert::AreEqual(1, validateSize(5), L"Valid input should return valid");
        }

        TEST_METHOD(NullInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateSize(NULL), L"Null input should return invalid");
        }

        TEST_METHOD(EmptyStringInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validateSize(0.0f), L"Empty string input should return invalid");
        }
    };

    TEST_CLASS(BlackBoxValidatePointTests)
    {
    public:
        // Test cases for validatePoint function
        TEST_METHOD(NegativeRowInput_ReturnsInvalid)
        {
            Assert::AreEqual(0, validatePoint(-3.5, 'B'), L"Negative row input should return invalid");
        }

        TEST_METHOD(ValidInput_ReturnsValid)
        {
            Assert::AreEqual(1, validatePoint(2.0, 'G'), L"Valid input should return valid");
        }

        TEST_METHOD(NullInputs_ReturnsInvalid)
        {
            Assert::AreEqual(0, validatePoint(NULL, 'H'), L"Null inputs should return invalid");
        }

        TEST_METHOD(EmptyStringInputs_ReturnsInvalid)
        {
            Assert::AreEqual(0, validatePoint(0.0, '\0'), L"Empty string inputs should return invalid");
        }
    };


    TEST_CLASS(BlackBoxEnoughSpaceTests)
    {
    public:
        // Test cases for enoughSpace function
        TEST_METHOD(TestEnoughSpace_EnoughSpaceAvailable)
        {
            // Arrange
            struct Truck truck = { 'B', 1000, 30, { {0, 0}, 5, 2 } };
            struct Shipment shipment = { 10.5, 5, {3, 3} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEnoughSpace_NotEnoughSpaceAvailable)
        {
            // Arrange
            struct Truck truck = { 'Y', 1100, 49, { {0, 0}, 5, 2 } };
            struct Shipment shipment = { 20, 5, {3, 3} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEnoughSpace_NullInputForTruck)
        {
            // Arrange
            struct Truck* truck = NULL;
            struct Shipment shipment = { 15, 3, {2, 2} };

            // Act
            int result = enoughSpace(&shipment, truck);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEnoughSpace_EmptyShipment)
        {
            // Arrange
            struct Truck truck = { 'G', 1000, 30, { {0, 0}, 5, 2 } };
            struct Shipment shipment = { 0, 0, {0, 0} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(1, result);
        }
    };

    TEST_CLASS(BlackBoxChooseTruckTests)
    {
    public:
        // Test cases for chooseTruck function
        TEST_METHOD(TestChooseTruck_FirstTruckEmptier)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {10, {'B', 1100, 30, { {0, 0}, 5, 2 }}},
                {10, {'Y', 1200, 40, { {0, 0}, 5, 2 }}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestChooseTruck_SecondTruckEmptier)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {10, {'B', 1000, 50, { {0, 0}, 5, 2 }}},
                {10, {'Y', 900, 20, { {0, 0}, 5, 2 }}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestChooseTruck_NullInputForDistances)
        {
            // Arrange
            struct DistanceWithTruck* distances = NULL;

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(TestChooseTruck_EqualTruckWeightsAndVolumes)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {10, {'B', 1000, 30, { {0, 0}, 5, 2 }}},
                {10, {'Y', 1000, 30, { {0, 0}, 5, 2 }}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(0, result);
        }
    };

    TEST_CLASS(BlackBoxEmptierTruckTests)
    {
    public:
        // Test cases for emptierTruck function
        TEST_METHOD(TestEmptierTruck_FirstTruckEmptier)
        {
            // Arrange
            double w1 = 1000, s1 = 30, w2 = 1100, s2 = 40;

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEmptierTruck_SecondTruckEmptier)
        {
            // Arrange
            double w1 = 1000, s1 = 30, w2 = 900, s2 = 20;

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEmptierTruck_BothTrucksEqualSpace)
        {
            // Arrange
            double w1 = 1000, s1 = 30, w2 = 1000, s2 = 30;

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEmptierTruck_NullInputForWeightsAndVolumes)
        {
            // Arrange
            double w1 = NULL, s1 = 0, w2 = 0, s2 = 0;

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }
    };

    ////////////////////// END OF BLACKBOX TEST //////////////////////////////

    /* CHOOSE ANOTHER FUNCTION, SOMETHING EASIER AND LESS COMPLEX
    TEST_CLASS(BlackShipmentTests)
    {
    public:
        
        // Test cases for validateShip function
        TEST_METHOD(ValidateShip_ValidShipment_ReturnsTrue)
        {
            struct Shipment shipment = { 0, 0, {0,0} };
            shipment.weight = 10.5;
            shipment.size = 5;
            shipment.destination.row = 1;
            shipment.destination.col = 1;
            Assert::IsTrue(validateShip(&shipment),L"error message"); // Valid shipment
        }
        
        TEST_METHOD(ValidateShip_InvalidWeight_ReturnsFalse)
        {
            struct Shipment shipment;
            shipment.weight = 30;
            shipment.size = 5;
            shipment.destination.row = 1;
            shipment.destination.col = 'A';
            Assert::IsFalse(validateShip(&shipment)); // Invalid weight
        }

        TEST_METHOD(ValidateShip_InvalidSize_ReturnsFalse)
        {
            struct Shipment shipment;
            shipment.weight = 10;
            shipment.size = 2;
            shipment.destination.row = 1;
            shipment.destination.col = 'A';
            Assert::IsFalse(validateShip(&shipment)); // Invalid size
        }

        TEST_METHOD(ValidateShip_InvalidDestination_ReturnsFalse)
        {
            struct Shipment shipment;
            shipment.weight = 10;
            shipment.size = 5;
            shipment.destination.row = 1;
            shipment.destination.col = 'Z';
            Assert::IsFalse(validateShip(&shipment)); // Invalid destination
        }
        
    };
    */
    /////////////////////////WHITE BOX //////////////////////////
    TEST_CLASS(WhiteValidateWeightTests)
    {
    public:
        // Test cases for validateWeight function
        TEST_METHOD(ValidateWeight_ValidWeight_ReturnsTrue)
        {
            Assert::IsTrue(validateWeight(10), L"error message"); // Valid weight
        }

        TEST_METHOD(ValidateWeight_InvalidWeight_BelowRange_ReturnsFalse)
        {
            Assert::IsFalse(validateWeight(0), L"error message"); // Invalid weight, below valid range
        }

        TEST_METHOD(ValidateWeight_InvalidWeight_AboveRange_ReturnsFalse)
        {
            Assert::IsFalse(validateWeight(1500), L"error message"); // Invalid weight, above valid range
        }

        TEST_METHOD(ValidateWeight_InvalidWeight_Negative_ReturnsFalse)
        {
            Assert::IsFalse(validateWeight(-5), L"error message"); // Invalid weight, negative number
        }
    };
   
    TEST_CLASS(WhiteValidateSizeTests)
    {
    public:
        // Test cases for validateSize function
        TEST_METHOD(ValidateSize_ValidSize_ReturnsTrue)
        {
            Assert::IsTrue(validateSize(5), L"error message"); // Valid size
        }

        TEST_METHOD(ValidateSize_InvalidSize_ExceedsMaximumSize_ReturnsFalse)
        {
            Assert::IsFalse(validateSize(600), L"error message"); // Invalid size, exceeds maximum size
        }

        TEST_METHOD(ValidateSize_InvalidSize_Negative_ReturnsFalse)
        {
            Assert::IsFalse(validateSize(-1), L"error message"); // Invalid size, negative number
        }

        TEST_METHOD(ValidateSize_InvalidSize_DecimalFloat_ReturnsFalse)
        {
            Assert::IsFalse(validateSize(0.25), L"error message"); // Invalid size, decimal float
        }
    };
    
    TEST_CLASS(WhiteValidatePointTests)
    {
    public:
        // Test cases for validatePoint function
        TEST_METHOD(ValidatePoint_ValidPoint_ReturnsTrue)
        {
            Assert::IsTrue(validatePoint(5, 'A'), L"error message"); // Valid point
        }

        TEST_METHOD(ValidatePoint_InvalidRow_BelowRange_ReturnsFalse)
        {
            Assert::IsFalse(validatePoint(12, 'a'), L"error message"); // Invalid row, below valid range
        }

        TEST_METHOD(ValidatePoint_InvalidRow_AboveRange_ReturnsFalse)
        {
            Assert::IsFalse(validatePoint(26, 'A'), L"error message"); // Invalid row, above valid range
        }

        TEST_METHOD(ValidatePoint_InvalidColumn_ReturnsFalse)
        {
            Assert::IsFalse(validatePoint(5, '@'), L"error message"); // Invalid column
        }
    };
    
    
    //UPDATED WHITEBOX TEST CASE FOR ENOUGHSPACE FUNCTION 
    
    TEST_CLASS(WhiteBoxEnoughSpaceTests)
    {
    public:
        // Test cases for enoughSpace function
        TEST_METHOD(TestEnoughSpace_ValidData_ReturnsTrue)
        {
            //Pass the values to struct truck and shipment 
            struct Truck truck = { 'Y', 900, 20, { {1, 0}, 8, 3 } };
            struct Shipment shipment = { 100, 10, {5, 3} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEnoughSpace_OverBound_ReturnsFalse)
        {
          //Pass the values to struct truck and shipment 
            struct Truck truck = { 'B', 1100, 30, { {2, 0}, 6, 9 } };
            struct Shipment shipment = { 400, 30, {4, 8} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEnoughSpace_MaximumEdge_ReturnsTrue)
        {
             //Pass the values to struct truck and shipment 
            struct Truck truck = { 'G', 1100, 40, { {2, 0}, 2, 19 } };
            struct Shipment shipment = { 100, 10, {2, 11} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEnoughSpace_InvalidData_ReturnsFalse)
        {
            //Pass the values to struct truck and shipment 
            struct Truck truck = { 'B', '%$&', 30, { {2, 0}, 6, 9 } };
            struct Shipment shipment = { 2, 30, {4, 8} };

            // Act
            int result = enoughSpace(&shipment, &truck);

            // Assert
            Assert::AreEqual(0, result);
        }
    };
    
    //Whitebox testing for emptier truck function//
    
    TEST_CLASS(WhiteBoxEmptierTruckTests)
    {
    public:

        // Test cases for emptierTruck function

        TEST_METHOD(TestEmptierTruck_BothTrucksFull_ReturnsFalse) //Maximum Edge Case
        {
            // Pass the data into the function for both of the trucks
            double w1 = 1200, s1 = 50, w2 = 1200, s2 = 50;

            // Act
            //truck1 is w1,s1 and truck2 is w2,s2
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEmptierTruck_OverBoundsValue_ReturnsFalse)
        {
            // Pass the data into the function for both of the trucks
            double w1 = 1300, s1 = 60, w2 = 1400, s2 = 60; //weight and size ae out of bounds

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }

        TEST_METHOD(TestEmptierTruck_SecondTruckisEmptier_ReturnsTrue)
        {
            // Pass the data into the function for both of the trucks
            double w1 = 1100, s1 = 40, w2 = 900, s2 = 20;

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(1, result);
        }

        TEST_METHOD(TestEmptierTruck_InvalidData_ReturnsFalse)
        {
            // Pass the data into the function for both of the trucks
            double w1 = '-+@', s1 = '*', w2 = 'abcd', s2 = 'mn';

            // Act
            int result = emptierTruck(w1, s1, w2, s2);

            // Assert
            Assert::AreEqual(0, result);
        }
    };
    //Whitebox testing for chooseTruck function
    
    TEST_CLASS(WhiteBoxChooseTruckTests)
    {
    public:
        // Test where the second truck is emptier
        TEST_METHOD(ChooseTruck_ReturnsTrue)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {10, {'B', 1100, 40, { {0, 0}, 10, 2 }}},
                {10, {'Y', 1000, 40, { {0, 0}, 10, 2 }}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(1, result);
        }

        // Test where both trucks have different distances from the destination
        TEST_METHOD(ChooseTruck_ReturnsFalse)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {5, {'B', 1000, 30, { {0, 0}, 5, 2 }}},
                {10, {'Y', 1100, 40, { {0, 0}, 10, 2 }}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(0, result);
        }

        // Test with invalid data input
        TEST_METHOD(ChooseTruck_InvalidData_ReturnsFalse)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {0, {'B', 0, 200, {0, 0}}},
                {0, {'B', 120, 280, {0, 0}}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(0, result);
        }

        // Test where the first truck is emptier
        TEST_METHOD(ChooseTruck_ReturnsFalse2)
        {
            // Arrange
            struct DistanceWithTruck distances[2] = {
                {5,{'B',100, 20, {50, 0}}},
                {5,{'B',20, 200, {50, 0}}}
            };

            // Act
            int result = chooseTruck(distances);

            // Assert
            Assert::AreEqual(0, result);
        }
    };
        
    /* CHOOSE ANOTHER FUNCTION, SOMETHING EASIER AND LESS COMPLEX
    TEST_CLASS(WhiteValidateExitTests)
    {
    public:
        // Test cases for validateExit function
        TEST_METHOD(ValidateExit_ValidExitCommand_ReturnsTrue)
        {
            Assert::AreEqual(validateExit(0, '0'), 0); // Valid exit command
        }

        TEST_METHOD(ValidateExit_InvalidExitCommand_NonZeroWeight_ReturnsNull)
        {
            Assert::AreEqual(validateExit(5, '0'), 0); // Invalid exit command, non-zero weight
        }

        TEST_METHOD(ValidateExit_InvalidExitCommand_NonZeroSize_ReturnsNull)
        {
            Assert::AreEqual(validateExit(0, '5'), 0); // Invalid exit command, non-zero size
        }

        TEST_METHOD(ValidateExit_InvalidExitCommand_NonXCharacter_ReturnsNull)
        {
            Assert::AreEqual(validateExit(0, 'Y'), 0); // Invalid exit command, non 'X' character
        }
    };
    
    
    TEST_CLASS(WhitePrintBuslineTests)
    {
    public:
        // Test cases for printBusline function
        TEST_METHOD(PrintBusline_ValidBlueLine_ReturnsCorrectString)
        {
            Assert::AreEqual("Ship on BLUE LINE, ", printBusline('B')); // Valid blue line
        }

        TEST_METHOD(PrintBusline_ValidYellowLine_ReturnsCorrectString)
        {
            Assert::AreEqual("Ship on YELLOW LINE, ", printBusline('Y')); // Valid yellow line
        }

        TEST_METHOD(PrintBusline_ValidGreenLine_ReturnsCorrectString)
        {
            Assert::AreEqual("Ship on GREEN LINE, ", printBusline('G')); // Valid green line
        }

        TEST_METHOD(PrintBusline_InvalidTruckID_ReturnsErrorString)
        {
            Assert::AreEqual("Error truckID", printBusline('X')); // Invalid truck ID
        }
    };
    */
    /*funtions:
    * 1 - validateWeight
    * 2 - validateSize
    * 3 - validatePoint
    * 4 - enoughSpace - truck.c
    * 5 - chooseTruck - truck.c
    * 6 - emptierTruck - truck.c
    */

    ////////////////////// END OF WHITE TEST //////////////////////////////

    ////////////////////// INTEGRATION TESTS //////////////////////////////

    TEST_CLASS(IntegrationTestValidateShip)
    {
    public:
        TEST_METHOD(CorrectData)
        {
            //Variables
            float weight = 0, size = 0;
            char col = 'X';
            int row = 0;
            int result = 0;
            struct Shipment currentClient = { 0 };
            
            //Correct Data
            weight = 1000;
            size = 5;
            row = 19;
            col = 'G';
            
            //Testing the Data
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            // Verifications
            Assert::AreNotEqual(result, -1);
            Assert::AreEqual(currentClient.weight, 1000.0f);
            Assert::AreEqual(currentClient.size, 5.0f);
            Assert::AreEqual(currentClient.destination.col,6);
            Assert::AreEqual(currentClient.destination.row, 18);
        }

        TEST_METHOD(IncorrectWeight)
        {
            //Variables
            float weight = 0, size = 0;
            char col = 'X';
            int row = 0;
            int result = 0;
            struct Shipment currentClient = { 0 };

            //Incorrect Data
            weight = -1;
            //Correct Data
            size = 5;
            row = 19;
            col = 'G';

            //Testing the Data
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            // Verifications
            Assert::AreEqual(result, 0);
            Assert::AreNotEqual(currentClient.weight, 1000.0f);
            Assert::AreNotEqual(currentClient.size, 5.0f);
            Assert::AreNotEqual(currentClient.destination.col, 6);
            Assert::AreNotEqual(currentClient.destination.row, 18);
        }

        TEST_METHOD(IncorrectSize)
        {
            //Variables
            float weight = 0, size = 0;
            char col = 'X';
            int row = 0;
            int result = 0;
            struct Shipment currentClient = { 0 };

            //Incorrect Data
            size = 4;
            //Correct Data
            weight = 1000;
            row = 19;
            col = 'G';

            //Testing the Data
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            // Verifications
            Assert::AreEqual(result, 0);
            Assert::AreEqual(currentClient.weight, 1000.0f);
            Assert::AreNotEqual(currentClient.size, 5.0f);
            Assert::AreNotEqual(currentClient.destination.col, 6);
            Assert::AreNotEqual(currentClient.destination.row, 18);
        }

        TEST_METHOD(IncorrectPoint)
        {
            //Variables
            float weight = 0, size = 0;
            char col = 'X';
            int row = 0;
            int result = 0;
            struct Shipment currentClient = { 0 };

            //Incorrect Data
            row = 30;
            //Correct Data
            weight = 1000;
            size = 5;
            col = 'G';

            //Testing the Data
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            // Verifications
            Assert::AreEqual(result, 0);
            Assert::AreEqual(currentClient.weight, 1000.0f);
            Assert::AreEqual(currentClient.size, 5.0f);
            Assert::AreNotEqual(currentClient.destination.col, 29);
            Assert::AreNotEqual(currentClient.destination.row, 18);
        }
    };

    TEST_CLASS(IntegrationTestFindTruck)
    {
    public:
        TEST_METHOD(BlueIsCloser)
        {
            //Constants
            struct Truck trucks[3];
            int numTrucks = 3;

            //Variables
            float weight = 1000, size = 5;
            char col = 'L';
            int row = 12;
            int result = 0;
            char truckID = 'X';
            int divert = 0;
            struct Point startPoint = { 0 };

            //Filling Data
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }
            createTrucks(trucks);
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);

            //Testing id of the closer Truck
            Assert::AreEqual('B',truckID);
        }

        TEST_METHOD(YellowIsCloser)
        {
            //Constants
            struct Truck trucks[3];
            int numTrucks = 3;

            //Variables
            float weight = 1000, size = 5;
            char col = 'H';
            int row = 21;
            int result = 0;
            char truckID = 'X';
            int divert = 0;
            struct Point startPoint = { 0 };

            //Filling Data
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }
            createTrucks(trucks);
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);

            //Testing id of the closer Truck
            Assert::AreEqual('Y', truckID);
        }

        TEST_METHOD(GreenIsCloser)
        {
            //Constants
            struct Truck trucks[3];
            int numTrucks = 3;

            //Variables
            float weight = 1000, size = 5;
            char col = 'Y';
            int row = 8;
            int result = 0;
            char truckID = 'X';
            int divert = 0;
            struct Point startPoint = { 0 };

            //Filling Data
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }
            createTrucks(trucks);
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);

            //Testing id of the closer Truck
            Assert::AreEqual('G', truckID);
        }

        TEST_METHOD(BlueIsEmptier)
        {
            //Constants
            struct Truck trucks[3];
            int numTrucks = 3;

            //Variables
            float weight = 1000, size = 5;
            char col = 'Y';
            int row = 8;
            int result = 0;
            char truckID = 'X';
            int divert = 0;
            struct Point startPoint = { 0 };


            //Filling Data
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }
            createTrucks(trucks);
            trucks[2].weight = 1000;
            truckID = findTruck(&currentClient, trucks, numTrucks, &divert, &startPoint);

            //Testing id of the closer Truck
            Assert::AreEqual('B', truckID);
        }
    };

    TEST_CLASS(IntegrationTestEnoughSpace)
    {
    public:
        TEST_METHOD(GreenIsCorrect)
        {
            // Constants
            struct Map map = populateMap();
            struct Truck trucks[3];
            int numTrucks = 3;
            int blue = 0, yellow = 0, green = 0, index = 0;
            char truckID = 'X';
            struct DistanceWithTruck distances[3] = { 0 };
            struct Point startPoints[3] = { 0 };
            struct Point startPoint = { 0 };
            //Variables
            float weight = 1000, size = 5;
            char col = 'Y';
            int row = 8;
            int result = 0;
            //Filling data
            createTrucks(trucks);
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            //Integration Functions
            if (enoughSpace(&currentClient, &trucks[0])) {
                blue = hasPoint(&trucks[0].route, &currentClient.destination);
                if (blue == -1) {
                    blue = shortestRouteToDestination(&map, &trucks[0].route, currentClient.destination);
                    startPoints[0] = trucks[0].route.points[blue];
                }
                else {
                    truckID = 'B';
                }
            }
            else {
                blue = 0;
            };
            if (enoughSpace(&currentClient, &trucks[1]) && truckID != 'B') {
                yellow = hasPoint(&trucks[1].route, &currentClient.destination);
                if (yellow == -1) {
                    yellow = shortestRouteToDestination(&map, &trucks[1].route, currentClient.destination);
                    startPoints[1] = trucks[1].route.points[yellow];
                }
                else {
                    truckID = 'Y';
                }
            }
            else {
                yellow = 0;
            };
            if (enoughSpace(&currentClient, &trucks[2]) && truckID != 'B' && truckID != 'Y') {
                green = hasPoint(&trucks[2].route, &currentClient.destination);
                if (green == -1) {
                    green = shortestRouteToDestination(&map, &trucks[2].route, currentClient.destination);
                    startPoints[2] = trucks[2].route.points[green];
                }
                else {
                    truckID = 'G';
                }
            }
            else {
                green = 0;
            };
            if (blue == 0 && yellow == 0 && green == 0) {
                truckID = 'X';
            }
            else if (truckID == 'X') {
                if (blue) {
                    distances[0].distance = distance(&(currentClient.destination), &startPoints[0]);
                    distances[0].truck = trucks[0];
                }
                else {
                    distances[0].distance = 1000;
                };
                if (yellow) {
                    distances[1].distance = distance(&(currentClient.destination), &startPoints[1]);
                    distances[1].truck = trucks[1];
                }
                else {
                    distances[1].distance = 1000;
                };
                if (green) {
                    distances[2].distance = distance(&(currentClient.destination), &startPoints[2]);
                    distances[2].truck = trucks[2];
                }
                else {
                    distances[2].distance = 1000;
                };
                for (int i = 0; i < numTrucks - 1; i++) {
                    for (int j = 0; j < numTrucks - i - 1; j++) {
                        if (distances[j].distance > distances[j + 1].distance) {
                            struct DistanceWithTruck temp = distances[j];
                            distances[j] = distances[j + 1];
                            distances[j + 1] = temp;
                        }
                    }
                };
                index = chooseTruck(distances);
                truckID = distances[index].truck.truckID;

                //Testing id of the correct Truck
                Assert::AreEqual('G', truckID);
            }
        }

        TEST_METHOD(BlueIsCorrect)
        {
            // Constants
            struct Map map = populateMap();
            struct Truck trucks[3];
            int numTrucks = 3;
            struct Point startPoint = { 0 };
            int blue = 0, yellow = 0, green = 0, index = 0;
            char truckID = 'X';
            struct DistanceWithTruck distances[3] = { 0 };
            struct Point startPoints[3] = { 0 };
            //Variables
            float weight = 1000, size = 5;
            char col = 'Y';
            int row = 17;
            int result = 0;
            //Filling data
            createTrucks(trucks);
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            //Integration Functions
            if (enoughSpace(&currentClient, &trucks[0])) {
                blue = hasPoint(&trucks[0].route, &currentClient.destination);
                if (blue == -1) {
                    blue = shortestRouteToDestination(&map, &trucks[0].route, currentClient.destination);
                    startPoints[0] = trucks[0].route.points[blue];
                }
                else {
                    truckID = 'B';
                }
            }
            else {
                blue = 0;
            };
            if (enoughSpace(&currentClient, &trucks[1]) && truckID != 'B') {
                yellow = hasPoint(&trucks[1].route, &currentClient.destination);
                if (yellow == -1) {
                    yellow = shortestRouteToDestination(&map, &trucks[1].route, currentClient.destination);
                    startPoints[1] = trucks[1].route.points[yellow];
                }
                else {
                    truckID = 'Y';
                }
            }
            else {
                yellow = 0;
            };
            if (enoughSpace(&currentClient, &trucks[2]) && truckID != 'B' && truckID != 'Y') {
                green = hasPoint(&trucks[2].route, &currentClient.destination);
                if (green == -1) {
                    green = shortestRouteToDestination(&map, &trucks[2].route, currentClient.destination);
                    startPoints[2] = trucks[2].route.points[green];
                }
                else {
                    truckID = 'G';
                }
            }
            else {
                green = 0;
            };
            if (blue == 0 && yellow == 0 && green == 0) {
                truckID = 'X';
            }
            else if (truckID == 'X') {
                if (blue) {
                    distances[0].distance = distance(&(currentClient.destination), &startPoints[0]);
                    distances[0].truck = trucks[0];
                }
                else {
                    distances[0].distance = 1000;
                };
                if (yellow) {
                    distances[1].distance = distance(&(currentClient.destination), &startPoints[1]);
                    distances[1].truck = trucks[1];
                }
                else {
                    distances[1].distance = 1000;
                };
                if (green) {
                    distances[2].distance = distance(&(currentClient.destination), &startPoints[2]);
                    distances[2].truck = trucks[2];
                }
                else {
                    distances[2].distance = 1000;
                };
                for (int i = 0; i < numTrucks - 1; i++) {
                    for (int j = 0; j < numTrucks - i - 1; j++) {
                        if (distances[j].distance > distances[j + 1].distance) {
                            struct DistanceWithTruck temp = distances[j];
                            distances[j] = distances[j + 1];
                            distances[j + 1] = temp;
                        }
                    }
                };
                index = chooseTruck(distances);
                truckID = distances[index].truck.truckID;

                //Testing id of the correct Truck
                Assert::AreEqual('B', truckID);
            }
        }

        TEST_METHOD(YellowIsCorrect)
        {
            // Constants
            struct Map map = populateMap();
            struct Truck trucks[3];
            int numTrucks = 3;
            struct Point startPoint = { 0 };
            int blue = 0, yellow = 0, green = 0, index = 0;
            char truckID = 'X';
            struct DistanceWithTruck distances[3] = { 0 };
            struct Point startPoints[3] = { 0 };
            //Variables
            float weight = 1000, size = 5;
            char col = 'N';
            int row = 23;
            int result = 0;
            //Filling data
            createTrucks(trucks);
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            //Integration Functions
            if (enoughSpace(&currentClient, &trucks[0])) {
                blue = hasPoint(&trucks[0].route, &currentClient.destination);
                if (blue == -1) {
                    blue = shortestRouteToDestination(&map, &trucks[0].route, currentClient.destination);
                    startPoints[0] = trucks[0].route.points[blue];
                }
                else {
                    truckID = 'B';
                }
            }
            else {
                blue = 0;
            };
            if (enoughSpace(&currentClient, &trucks[1]) && truckID != 'B') {
                yellow = hasPoint(&trucks[1].route, &currentClient.destination);
                if (yellow == -1) {
                    yellow = shortestRouteToDestination(&map, &trucks[1].route, currentClient.destination);
                    startPoints[1] = trucks[1].route.points[yellow];
                }
                else {
                    truckID = 'Y';
                }
            }
            else {
                yellow = 0;
            };
            if (enoughSpace(&currentClient, &trucks[2]) && truckID != 'B' && truckID != 'Y') {
                green = hasPoint(&trucks[2].route, &currentClient.destination);
                if (green == -1) {
                    green = shortestRouteToDestination(&map, &trucks[2].route, currentClient.destination);
                    startPoints[2] = trucks[2].route.points[green];
                }
                else {
                    truckID = 'G';
                }
            }
            else {
                green = 0;
            };
            if (blue == 0 && yellow == 0 && green == 0) {
                truckID = 'X';
            }
            else if (truckID == 'X') {
                if (blue) {
                    distances[0].distance = distance(&(currentClient.destination), &startPoints[0]);
                    distances[0].truck = trucks[0];
                }
                else {
                    distances[0].distance = 1000;
                };
                if (yellow) {
                    distances[1].distance = distance(&(currentClient.destination), &startPoints[1]);
                    distances[1].truck = trucks[1];
                }
                else {
                    distances[1].distance = 1000;
                };
                if (green) {
                    distances[2].distance = distance(&(currentClient.destination), &startPoints[2]);
                    distances[2].truck = trucks[2];
                }
                else {
                    distances[2].distance = 1000;
                };
                for (int i = 0; i < numTrucks - 1; i++) {
                    for (int j = 0; j < numTrucks - i - 1; j++) {
                        if (distances[j].distance > distances[j + 1].distance) {
                            struct DistanceWithTruck temp = distances[j];
                            distances[j] = distances[j + 1];
                            distances[j + 1] = temp;
                        }
                    }
                };
                index = chooseTruck(distances);
                truckID = distances[index].truck.truckID;

                //Testing id of the correct Truck
                Assert::AreEqual('Y', truckID);
            }
        }

        TEST_METHOD(EmptierTruck)
        {
            // Constants
            struct Map map = populateMap();
            struct Truck trucks[3];
            int numTrucks = 3;
            struct Point startPoint = { 0 };
            int blue = 0, yellow = 0, green = 0, index = 0;
            char truckID = 'X';
            struct DistanceWithTruck distances[3] = { 0 };
            struct Point startPoints[3] = { 0 };
            //Variables
            float weight = 1000, size = 5;
            char col = 'B';
            int row = 4;
            int result = 0;
            //Filling data
            createTrucks(trucks);
            struct Shipment currentClient = { 0 };
            result = validateWeight(weight);
            if (result) {
                currentClient.weight = weight;
                result = validateSize(size);
                if (result) {
                    currentClient.size = size;
                    result = validatePoint(row, col);
                    if (result) {
                        currentClient.destination.col = toCol(col);
                        currentClient.destination.row = row - 1;
                    }
                }
            }

            //Integration Functions
            trucks[0].weight = 1000;
            trucks[1].volume = 50;

            if (enoughSpace(&currentClient, &trucks[0])) {
                blue = hasPoint(&trucks[0].route, &currentClient.destination);
                if (blue == -1) {
                    blue = shortestRouteToDestination(&map, &trucks[0].route, currentClient.destination);
                    startPoints[0] = trucks[0].route.points[blue];
                }
                else {
                    truckID = 'B';
                }
            }
            else {
                blue = 0;
            };
            if (enoughSpace(&currentClient, &trucks[1]) && truckID != 'B') {
                yellow = hasPoint(&trucks[1].route, &currentClient.destination);
                if (yellow == -1) {
                    yellow = shortestRouteToDestination(&map, &trucks[1].route, currentClient.destination);
                    startPoints[1] = trucks[1].route.points[yellow];
                }
                else {
                    truckID = 'Y';
                }
            }
            else {
                yellow = 0;
            };
            if (enoughSpace(&currentClient, &trucks[2]) && truckID != 'B' && truckID != 'Y') {
                green = hasPoint(&trucks[2].route, &currentClient.destination);
                if (green == -1) {
                    green = shortestRouteToDestination(&map, &trucks[2].route, currentClient.destination);
                    startPoints[2] = trucks[2].route.points[green];
                }
                else {
                    truckID = 'G';
                }
            }
            else {
                green = 0;
            };
            if (blue == 0 && yellow == 0 && green == 0) {
                truckID = 'X';
            }
            else if (truckID == 'X') {
                if (blue) {
                    distances[0].distance = distance(&(currentClient.destination), &startPoints[0]);
                    distances[0].truck = trucks[0];
                }
                else {
                    distances[0].distance = 1000;
                };
                if (yellow) {
                    distances[1].distance = distance(&(currentClient.destination), &startPoints[1]);
                    distances[1].truck = trucks[1];
                }
                else {
                    distances[1].distance = 1000;
                };
                if (green) {
                    distances[2].distance = distance(&(currentClient.destination), &startPoints[2]);
                    distances[2].truck = trucks[2];
                }
                else {
                    distances[2].distance = 1000;
                };
                for (int i = 0; i < numTrucks - 1; i++) {
                    for (int j = 0; j < numTrucks - i - 1; j++) {
                        if (distances[j].distance > distances[j + 1].distance) {
                            struct DistanceWithTruck temp = distances[j];
                            distances[j] = distances[j + 1];
                            distances[j + 1] = temp;
                        }
                    }
                };
                index = chooseTruck(distances);
                truckID = distances[index].truck.truckID;

                //Testing id of the correct Truck
                Assert::AreEqual('G', truckID);
            }
        }
    };

    TEST_CLASS(IntegrationGettingPossibleMoves)
    {
    public:
        TEST_METHOD(RightIsCorrect)
        {
            //constants
            struct Route possible = { {0,0},0,0 };
            struct Map map = populateMap();
            struct Route answer = { {0,0},0, DIVERSION };
            int close = 0;
            // Variables
            struct Point last = { 4, 10 };
            struct Point current = {4, 11}; //5L
            struct Point dest = {9, 24}; //8Y

            //Integration functions
            possible = getPossibleMoves(&map, current, last);
            close = getClosestPoint(&possible, dest);
            if (close >= 0)
            {
                last = current;
                current = possible.points[close];
                addPtToRoute(&answer, current);
            }
            //Testing the correct output
            Assert::AreEqual(answer.points->col,12);
            Assert::AreEqual(answer.points->row,4);
        }

        TEST_METHOD(UpIsCorrect)
        {
            //constants
            struct Route possible = { {0,0},0,0 };
            struct Map map = populateMap();
            struct Route answer = { {0,0},0, DIVERSION };
            int close = 0;
            // Variables
            struct Point last = { 4, 9 };
            struct Point current = { 4, 10 }; //5K
            struct Point dest = { 2, 10 }; //3K

            //Integration functions
            possible = getPossibleMoves(&map, current, last);
            close = getClosestPoint(&possible, dest);
            if (close >= 0)
            {
                last = current;
                current = possible.points[close];
                addPtToRoute(&answer, current);
            }
            //Testing the correct output
            Assert::AreEqual(answer.points->col, 10);
            Assert::AreEqual(answer.points->row, 3);
        }

        TEST_METHOD(LeftIsCorrect)
        {
            //constants
            struct Route possible = { {0,0},0,0 };
            struct Map map = populateMap();
            struct Route answer = { {0,0},0, DIVERSION };
            int close = 0;
            // Variables
            struct Point last = { 4, 9 };
            struct Point current = { 7, 3 }; //8D
            struct Point dest = { 7, 1 }; //8B

            //Integration functions
            possible = getPossibleMoves(&map, current, last);
            close = getClosestPoint(&possible, dest);
            if (close >= 0)
            {
                last = current;
                current = possible.points[close];
                addPtToRoute(&answer, current);
            }
            //Testing the correct output
            Assert::AreEqual(answer.points->col, 2);
            Assert::AreEqual(answer.points->row, 7);
        }

        TEST_METHOD(DownIsCorrect)
        {
            //constants
            struct Route possible = { {0,0},0,0 };
            struct Map map = populateMap();
            struct Route answer = { {0,0},0, DIVERSION };
            int close = 0;
            // Variables
            struct Point last = { 4, 9 };
            struct Point current = { 19, 10 }; //20K
            struct Point dest = { 21, 10 }; //22K

            //Integration functions
            possible = getPossibleMoves(&map, current, last);
            close = getClosestPoint(&possible, dest);
            if (close >= 0)
            {
                last = current;
                current = possible.points[close];
                addPtToRoute(&answer, current);
            }
            //Testing the correct output
            Assert::AreEqual(answer.points->col, 10);
            Assert::AreEqual(answer.points->row, 20);
        }
    };
    ////////////////////// END OF INTEGRATION TESTS //////////////////////////////

    ///////////////////////// ACCEPTANCE TESTS //////////////////////////
    TEST_CLASS(AcceptanceTests)
    {
    public:

        // Test case for Invalid destination
        TEST_METHOD(Invaliddestination) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 20, size = 0.5;
            char col = 'X';
            int row = 28;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[21];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Invalid destination");

        }

        // Test case for Invalid size
        TEST_METHOD(Invalidsize) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 20, size = 3;
            char col = 'L';
            int row = 12;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[20];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap,weight,size,row,col,message);
            //Testing the output
            Assert::AreEqual(message,"Invalid size");
        }

        // Test case for Invalid weight
        TEST_METHOD(Invalidweight) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 1300, size = 0.5;
            char col = 'L';
            int row = 12;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[40];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Invalid weight (must be 1-1200 Kg.)");
        }

        // Test case for Ship on BLUE LINE, no diversion
        TEST_METHOD(ShipBnodiversion) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 20, size = 0.5;
            char col = 'L';
            int row = 12;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[100];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Ship on BLUE LINE, no diversion");
        }

        // Test case for Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y
        TEST_METHOD(ShipGdiversion) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            trucks[0].weight += 20;
            trucks[0].volume += 0.5;
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 500, size = 1.0;
            char col = 'Y';
            int row = 8;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[100];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y");
        }

        // Test case for Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y
        TEST_METHOD(ShipGdiversion2) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            trucks[0].weight += 20;
            trucks[0].volume += 0.5;
            trucks[2].weight += 500;
            trucks[2].volume += 1;
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 500, size = 1.0;
            char col = 'Y';
            int row = 8;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[100];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Ship on GREEN LINE, divert: 7T, 7U, 7V, 7W, 7X, 7Y, 8Y");
        }

        // Test case for Ship on BLUE LINE, divert 6J, 6K, 6L, 6M, 6N, 6O, 6P, 6Q, 6R, 6S, 6T, 6U, 6V, 6W, 6X, 7X, 7Y, 8Y
        TEST_METHOD(ShipBdiversion) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            trucks[0].weight += 20;
            trucks[0].volume += 0.5;
            trucks[2].weight += 500;
            trucks[2].volume += 1;
            trucks[2].weight += 500;
            trucks[2].volume += 1;
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 500, size = 1.0;
            char col = 'Y';
            int row = 8;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[100];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Ship on BLUE LINE, divert: 6J, 6K, 6L, 6M, 6N, 6O, 6P, 6Q, 6R, 6S, 6T, 6U, 6V, 6W, 6X, 7X, 7Y, 8Y");
        }

        // Test case for exit: Thanks for shipping with Seneca!
        TEST_METHOD(Exit) {
            /////// Initialization///////
            //Create the array for the trucks available
            struct Truck trucks[3];
            int numTrucks = 3;
            //Create the map for the trucks
            struct Map baseMap = populateMap();
            //add a route to each truck
            createTrucks(trucks);
            struct Map routeMap = addRoute(&baseMap, &trucks[0].route);
            routeMap = addRoute(&routeMap, &trucks[1].route);
            routeMap = addRoute(&routeMap, &trucks[2].route);
            ////////////////////////////
             ////// Variables to simulate user input //////
            float weight = 0, size = 0;
            char col = 'x';
            int row=0;
            ////////////////////////////
            ////// Variables to read the console output //////
            char message[38];
            ////////////////////////////
            getShipmentAT(trucks, numTrucks, &baseMap, weight, size, row, col, message);
            //Testing the output
            Assert::AreEqual(message, "Thanks for shipping with Seneca!");
        }
    };

    ///////////////////////// END OF ACCEPTANCE TESTS //////////////////////////
}
