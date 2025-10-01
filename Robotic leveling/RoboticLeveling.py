import unittest
from typing import List

__PRINT_DEBUG__ = False


def solve(claw_pos: int, boxes: List[int], box_in_claw: bool) -> str:
    print_debug(f"[solve] ARGS: claw_pos={claw_pos}, boxes={boxes}, box_in_claw={box_in_claw}")

    instruction = find_instruction(claw_pos, boxes, box_in_claw)

    print_debug(f"[solve] return: \"{instruction}\"")
    return instruction


def find_instruction(claw_pos: int, boxes: List[int], box_in_claw: bool) -> str:
    print_debug(f"[find_instruction] ARGS: claw_pos={claw_pos}, boxes={boxes}, box_in_claw={box_in_claw}")

    delta_boxes = find_delta_boxes(boxes, box_in_claw)
    instruction = ""
    if (delta_boxes[claw_pos] < 0 and not box_in_claw):
        instruction = "PICK"
    elif (delta_boxes[claw_pos] > 0 and box_in_claw):
        instruction = "PLACE"
    else:  # We're moving
        instruction = find_direction(claw_pos, delta_boxes, box_in_claw)

    print_debug(f"[find_instruction] return: \"{instruction}\"")
    return instruction


def find_delta_boxes(boxes: List[int], box_in_claw: bool) -> List[int]:
    print_debug(f"[find_delta_boxes] ARGS: boxes={boxes}, box_in_claw={box_in_claw}")

    target_boxes = find_target_boxes(boxes, box_in_claw)
    delta_boxes = [0] * len(boxes)
    for i in range(len(boxes)):
        delta_boxes[i] = target_boxes[i] - boxes[i]

    print_debug(f"[find_delta_boxes] return: {delta_boxes}")
    return delta_boxes


def find_target_boxes(boxes: List[int], box_in_claw: bool) -> List[int]:
    print_debug(f"[find_target_boxes] ARGS: boxes={boxes}, box_in_claw={box_in_claw}")

    total_boxes = sum(boxes)
    total_boxes += 1 if box_in_claw else 0
    total_stacks = len(boxes)
    print_debug(f"[find_target_boxes] total_boxes={total_boxes}, total_stacks={total_stacks}")
    target_boxes = [0] * total_stacks
    min_target = int(total_boxes / total_stacks)
    for i in range(total_stacks):
        target_boxes[i] = int(min_target)
    remaining = total_boxes % total_stacks
    if remaining > 0:
        for i in range(remaining):
            target_boxes[i] += 1

    print_debug(f"[find_target_boxes] return: {target_boxes}")
    return target_boxes


def find_direction(claw_pos: int, delta_boxes: List[int], box_in_claw: bool) -> str:
    print_debug(f"[find_direction] ARGS: claw_pos={claw_pos}, delta_boxes={delta_boxes}, box_in_claw={box_in_claw}")

    direction = ""
    if box_in_claw:
        for i in range(claw_pos):
            if delta_boxes[i] > 0:
                direction = "LEFT"
                break
        direction = "RIGHT" if direction == "" else "LEFT"
    else:
        for j in range(claw_pos):
            if delta_boxes[j] < 0:
                direction = "LEFT"
                break
        direction = "RIGHT" if direction == "" else "LEFT"

    print_debug(f"[find_direction] return: \"{direction}\"")
    return direction


def print_debug(msg: str) -> None:
    if __PRINT_DEBUG__:
        print(msg)


class find_direction_Tests(unittest.TestCase):
    def test_1(self):
        self.assertEqual(find_direction(0, [1, -1], False), "RIGHT")

    def test_2(self):
        self.assertEqual(find_direction(1, [-1, 1], False), "LEFT")


class solve_Tests(unittest.TestCase):
    def setUp(self):
        pass

    def test_simple_case_1(self):
        self.assertEqual(solve(0, [3, 1, 2, 2], False), "PICK")

    def test_simple_case_2(self):
        self.assertEqual(solve(0, [2, 1, 2, 2], True), "RIGHT")

    def test_simple_case_3(self):
        self.assertEqual(solve(1, [2, 1, 2, 2], True), "PLACE")

    def test_one_in_each_1(self):
        self.assertEqual(solve(0, [1, 0, 3, 0, 0, 1, 2], False), "RIGHT")

    def test_some_of_each_1(self):
        self.assertEqual(solve(0, [4, 2, 3, 4, 3, 2], False), "PICK")

    def test_offset_1(self):
        self.assertEqual(solve(4, [0, 2, 1, 0, 0, 1], False), "LEFT")


if __name__ == "__main__":
    unittest.main()
