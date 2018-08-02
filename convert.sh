# Convert to smaller, monochrome
convert original.jpg -monochrome -resize 320x240 output.jpg
# Convert to gray samples
convert output.jpg gray:output.gray

# Convert back from monchrome samples to jpg (unnecessary)
convert -size 320x240 -depth 8 output.gray rebuild.jpg

# Convert monchrome JPG to RGB colorspace
convert rebuild.jpg -colorspace sRGB -type truecolor rebuild.jpg

# Draw at a point
convert rebuild.jpg -fill red -draw 'color 5,5 point' colored.jpg
convert colored.jpg -fill red -draw 'color 5,4 point' colored.jpg
convert colored.jpg -fill red -draw 'color 5,6 point' colored.jpg
convert colored.jpg -fill red -draw 'color 4,5 point' colored.jpg
convert colored.jpg -fill red -draw 'color 6,5 point' colored.jpg

# Cleanup
# rm output.gray
rm output.jpg
rm rebuild.jpg