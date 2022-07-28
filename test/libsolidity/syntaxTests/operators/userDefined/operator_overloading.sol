type Int is uint128;

using {add as +, add128 as +} for Int;

function add(Int, Int) returns (Int) {}
function add128(Int, int128) returns (Int) {}

function test() {
    Int.wrap(0) + Int.wrap(1);
}
// ----
// TypeError 1884: (117-130): Wrong parameters in operator definition. The function "add128" needs to have two parameters of type Int and the same data location to be used for the operator +.
// TypeError 5583: (171-196): User-defined binary operator + has more than one definition matching the operand types visible in the current scope.
