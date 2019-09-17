'This is a string, in Turbo Pascal it must be written on a single line'
'if it is not, what should a compiler do then?'
'well it throws an error but it is not appearing until after many operations'

'now testing what the lexer will to with a string'
'that spans multiple lines, which is illegal in TURBO pascal'

{this is a regular well formed comment....}
{
the same
comment
that spans
muliple lines
}

(* and this is another type of the same comment....*)

(*
now a star comment
spanning many lines
hell yeaahhh *}

(* now testing a single star * in the comment but newer properly ending it => should throw an exception


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

'his should be unknown'
.45e2

'some identifiers'
var1
_ble99

'but this is illegal'
9_ab

