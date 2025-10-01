'''
    CoderPad question: Find the temperature (Difficulty: Medium, Duration 20:00)

    Your company builds temperature captors for freezers.
    The captors records temperature periodically and put the last values in a list.
    You have to develop the algorithm displaying the unique temperature that is supposed to sum up these values.

    You know the captors are not reliable at all, so you decide to display the most expected temperature among
    the ones in the list, which is the one closest to zero.

    Implement the function 'closest_to_zero(ts)'.
        * the list 'ts' is always defined (no null, None or any other value like that)
        * 'ts' can be empty, in that case, return the value 0 (zero)
        * if two numbers in 'ts' are as close to zero, consider the positive number as the closest
        * the temperature are always expressed with decimal numbers ranging from -273.0 to 5526.0
'''

from typing import List
import unittest


def closest_to_zero(ts: List[float]) -> float:
    '''

    Args:

        - ts (List[float]): the temperatures measured by the captor.

    Returns:

        the temperature closest to zero.
    '''

    # Write your code here
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)

    if len(ts) == 0:
        return 0

    closest = 5526.0
    for t in ts:
        if abs(t) < abs(closest):
            closest = t
        elif t == -closest:
            closest = abs(t)
        # print(f"t = {t}, abs(t) = {abs(t)}, closest = {closest}")

    return closest


class closest_to_zero_Tests(unittest.TestCase):
    def setUp(self):
        pass

    def test_simple_test(self):
        self.assertEqual(closest_to_zero([7.2, 2.4, 9.6, -5.7, 4]), 2.4)

    def test_two_temperatures_that_are_as_close_to_0__negative_one_is_first_in_the_array(self):
        self.assertEqual(closest_to_zero([15, -7.1, 9.2, 14.3, 7.1, 12.9]), 7.1)

    def test_two_temperatures_that_are_as_close_to_0__positive_one_is_first_in_the_array(self):
        self.assertEqual(closest_to_zero([15, 7.1, 9.2, 14.3, -7.1, 12.9]), 7.1)

    def test_maximum_heat(self):
        self.assertEqual(closest_to_zero([5526]), 5526)

    def test_ultra_frozen(self):
        self.assertEqual(closest_to_zero([-273]), -273)

    def test_only_negative_values(self):
        self.assertEqual(closest_to_zero([-15.8, -50.7, -9.6, -14.5, -9.7]), -9.6)

    def test_twice_the_same_value__negative(self):
        self.assertEqual(closest_to_zero([-10, -10]), -10)

    def test_a_zero_at_the_end_of_the_array(self):
        self.assertEqual(closest_to_zero([10.5, -10.5, -20.1, -20.1, 0]), 0)

    def test_empty_array(self):
        self.assertEqual(closest_to_zero([]), 0)


if __name__ == "__main__":
    unittest.main()
