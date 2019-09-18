'This is a string, in Turbo Pascal it must be written on a single line'
'if it is not, what should a compiler do then?'
'well it throws an error'

'now testing what the lexer will to with a string'
'that spans multiple lines, which is illegal in TURBO pascal'

{this is a regular well formed comment....}

{
the same
comment
that spans
muliple lines
}

(* and this is * another type of the same comment....*)

(*
now a star comment
spanning many lines
hell yeaahhh *)

here are some words I want to grab between comments

'integers of various formats'
-1
-0234
1234
0

Reals
0.0
100E1
99.99
-99.100E-089
-248E8
499E+45
-45.43e-23

'this should be unknown add to the specs'
.45e2

'some identifiers'
var1
_ble99

'but this is illegal'
9_ab

'operators and punctation'
1 + 1
2 - 2
3 * 3
4 / 4
5 ^ 5
7 <> 8
9 <= 9
10 < 11
13 > 12
14 >= 14
15 == 15
a := 0
;
:
..
,
.
()
[]

'keysword'
absolute
and
array
begin
boolean
byte
case
char
const
div
do
downto
else
end
external
false
file
forward
for
function
goto
if
in
integer
inline
label
mod
nil
not
of
or
overlay
packed
procedure
program
real
record
repeat
set
shl
shr
string
then
to
true
name
until
var
while
with
xor