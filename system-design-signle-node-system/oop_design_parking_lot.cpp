/*
  https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/parking_lot/parking_lot.ipynb

Design a parking lot
Constraints and assumptions

What types of vehicles should we support?
Motorcycle, Car, Bus
Does each vehicle type take up a different amount of parking spots?
Yes
Motorcycle spot -> Motorcycle
Compact spot -> Motorcycle, Car
Large spot -> Motorcycle, Car
Bus can park if we have 5 consecutive "large" spots
Does the parking lot have multiple levels?
Yes


https://www.codeconvert.ai/python-to-c++-converter
converted example by Donne Martin in python
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

enum class VehicleSize {
    MOTORCYCLE = 0,
    COMPACT = 1,
    LARGE = 2
};

class Vehicle {
public:
    Vehicle(VehicleSize vehicle_size, const std::string& license_plate, int spot_size)
        : vehicle_size(vehicle_size), license_plate(license_plate), spot_size(spot_size), spots_taken() {}

    void clear_spots() {
        for (auto spot : spots_taken) {
            spot->remove_vehicle(this);
        }
        spots_taken.clear();
    }

    void take_spot(std::shared_ptr<ParkingSpot> spot) {
        spots_taken.push_back(spot);
    }

    virtual bool can_fit_in_spot(std::shared_ptr<ParkingSpot> spot) = 0;

protected:
    VehicleSize vehicle_size;
    std::string license_plate;
    int spot_size;
    std::vector<std::shared_ptr<ParkingSpot>> spots_taken;
};

class Motorcycle : public Vehicle {
public:
    Motorcycle(const std::string& license_plate)
        : Vehicle(VehicleSize::MOTORCYCLE, license_plate, 1) {}

    bool can_fit_in_spot(std::shared_ptr<ParkingSpot> spot) override {
        return true;
    }
};

class Car : public Vehicle {
public:
    Car(const std::string& license_plate)
        : Vehicle(VehicleSize::COMPACT, license_plate, 1) {}

    bool can_fit_in_spot(std::shared_ptr<ParkingSpot> spot) override {
        return spot->spot_size == static_cast<int>(VehicleSize::LARGE) || spot->spot_size == static_cast<int>(VehicleSize::COMPACT);
    }
};

class Bus : public Vehicle {
public:
    Bus(const std::string& license_plate)
        : Vehicle(VehicleSize::LARGE, license_plate, 5) {}

    bool can_fit_in_spot(std::shared_ptr<ParkingSpot> spot) override {
        return spot->spot_size == static_cast<int>(VehicleSize::LARGE);
    }
};

class ParkingLot {
public:
    ParkingLot(int num_levels)
        : num_levels(num_levels), levels() {}

    bool park_vehicle(std::shared_ptr<Vehicle> vehicle) {
        for (auto& level : levels) {
            if (level->park_vehicle(vehicle)) {
                return true;
            }
        }
        return false;
    }

private:
    int num_levels;
    std::vector<std::shared_ptr<Level>> levels;
};

class Level {
public:
    static const int SPOTS_PER_ROW = 10;

    Level(int floor, int total_spots)
        : floor(floor), num_spots(total_spots), available_spots(0), parking_spots() {}

    void spot_freed() {
        available_spots++;
    }

    bool park_vehicle(std::shared_ptr<Vehicle> vehicle) {
        auto spot = find_available_spot(vehicle);
        if (spot) {
            spot->park_vehicle(vehicle);
            return true;
        }
        return false;
    }

private:
    std::shared_ptr<ParkingSpot> find_available_spot(std::shared_ptr<Vehicle> vehicle) {
        // Implement the logic to find an available spot where the vehicle can fit
    }

    void park_starting_at_spot(std::shared_ptr<ParkingSpot> spot, std::shared_ptr<Vehicle> vehicle) {
        // Implement the logic to occupy the spots starting from the given spot
    }

    int floor;
    int num_spots;
    int available_spots;
    std::vector<std::shared_ptr<ParkingSpot>> parking_spots;
};

class ParkingSpot {
public:
    ParkingSpot(std::shared_ptr<Level> level, int row, int spot_number, int spot_size, VehicleSize vehicle_size)
        : level(level), row(row), spot_number(spot_number), spot_size(spot_size), vehicle_size(vehicle_size), vehicle(nullptr) {}

    bool is_available() {
        return vehicle == nullptr;
    }

    bool can_fit_vehicle(std::shared_ptr<Vehicle> vehicle) {
        if (vehicle == nullptr) {
            return false;
        }
        return vehicle->can_fit_in_spot(this); // LZ make sure this is a shared_ptr or can be cast to one
    }

    void park_vehicle(std::shared_ptr<Vehicle> vehicle) {
        // Implement the logic to park the vehicle in the spot
    }

    void remove_vehicle() {
        // Implement the logic to remove the vehicle from the spot
    }

private:
    std::shared_ptr<Level> level;
    int row;
    int spot_number;
    int spot_size;
    VehicleSize vehicle_size;
    std::shared_ptr<Vehicle> vehicle;
};

