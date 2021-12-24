//
// Created by 安炳旭 on 2020-01-06.
//

int JumpFloorII(int target) {
    return target <= 0 ? 0 : 1 << (target - 1);
}