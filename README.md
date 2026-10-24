# Stykkevis

Stykkevis is a digital PWL string generator from a binary sequence or multiple binary sequences separated by comma.

# How to use
provide to the binary these parameters:
- vl: voltage low (in volts)
- vh: voltage high (in volts)
- tr: time of rising edge
- tf: time of falling edge
- p: perdiod
- tu: time unit (for tr and tf)
- vu: voltage unit (for vl and vh)
- pf: prefix or prefix template. Each string of binary sequence will be prefixed with the prefix or the prefix template. The schema is defined by including '@' placeholder, then the placeholder will be replaced by letters A to Z on each binary sequence.
- bs: binary sequence

# Example usage:
The command:
<code>stykkevis -bs 01,10 -pf "V@ @ VSS"</code>
Will produce:
<code>VA A VSS PWL( 0 0 1 0 100 0 101 1.2 200 1.2 )
      VB B VSS PWL( 0 0 1 1.2 100 1.2 101 0 200 0 )</code>

