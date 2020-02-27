echo $1
rm -f flash.hex
od -v -A n -t x1 --width=1 $1 > flash_byte.hex
echo //Flash data for soc simv > flash.hex
echo @000 >> sfdb_4m.vmf
awk '{print $1}' flash_byte.hex >> flash.hex
rm flash_byte.hex

