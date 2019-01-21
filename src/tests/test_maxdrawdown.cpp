#include <iostream>
#include <vector>
#include <string>


void calcMaxDrawDown(const std::vector<double>& nums)
{
    if (nums.empty()) { return; }
    double maxDrawDown = 0;
    double high = nums[0];
    for(int i = 1; i < nums.size(); i++)
    {
        if (high < nums[i]) {
            high = nums[i];
        }

        if (high - nums[i] > maxDrawDown) {
            maxDrawDown = high - nums[i];
        }

    }
    std::cout << "max draw down is:" << maxDrawDown*-1.0 << std::endl;
}

int main()
{
    std::vector<double> nums = { 100, 90, 110, 90, 100, 99};
    calcMaxDrawDown(nums);

    return 0;
}
