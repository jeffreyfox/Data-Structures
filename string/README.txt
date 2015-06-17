LSD string sort: suitable for fix length strings, need to examine all digits. If R is large (Unicode), overhead increases significantly. If alphabet set is not numbers, we could find a mapping from each alphabet to its index (e.g. A=>0, C=>1, G=>2, T=>3)

MSD string sort: suitable for variable length strings. Additional count field for string of length less than current digit number. Since a goes before ab, empty string's count field should come before all othe radices. The trick is to set properly the subarray ranges in recursive sort routine. Note that in the recursive routine, we only need to sort subarrays whose d+1's digit is not empty (r = 0 .. R-1), thus avoiding sorting the subarray with empty d's digit again.
MSD sort can be adapted to fix length strings, but we can remove the empty string's count field, and stop when d == W. Similarly with LSD sort, MSD sort also has large time/space overhead for small subarrays (aux/count array, counting/redistributing elements). It's better to use insertion sort for small subarrays. 

3-way string quicksort: suitable for strings with long prefix matches (many duplicated parts).

