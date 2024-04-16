#!/bin/sh

cat <<EOF | xmenu
'[]=' Tiled Layout	0
'><>' Floating Layout	1
'[M]' Monocle Layout	2
'[@]' Spiral  Layout	3
'[\\]' Dwindle Layout	4
'H[]' Deck  Layout 	5
'TTT' Bstack Layout	6
'===' Bstackhoriz Layout 7
'HHH' Grid Layout	8
'###' Nrowgrid Layout 9
'---' Horizgrid Layout	10
':::' Gaplessgrid Layout 11
'|M|' Centeredmaster Layout	12
'>M>' Centeredfloatingmaster Layout	13
EOF