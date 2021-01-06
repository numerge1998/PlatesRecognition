import cv2
import pytesseract as tess
import re
import argparse

def check_plate(str):
	file = open('plates.txt', 'r')
	lines = file.read().splitlines()
	#print(str)
	for line in lines:
		#print(line)
		if line == str:
			return True
	return False

	
parser = argparse.ArgumentParser()
parser.add_argument('nr', type=int,)
args = parser.parse_args()

img = cv2.imread(str(args.nr) + '.jpg')
text = tess.image_to_string(img)
regex = "((AB)|(AR)|(AG)|B|(BC)|(BH)|(BN)|(BT)|(BV)|(BR)|(BZ)|(CS)|(CL)|(CJ)|(CT)|(CV)|(DB)|(DJ)|(GL)|(GR)|(GJ)|(HR)|(HD)|(IL)|(IS)|(IF)|(MM)|(MH)|(MS)|(NT)|(OT)|(PH)|(SM)|(SJ)|(SB)|(SV)|(TR)|(TM)|(TL)|(VS)|(VL)|(VN)) [0-9]{2,3} [A-Z]{3}"
text = text.replace('|','')
print(text)
cv2.imshow("out",img)
	
if re.match(regex,text):
	print("Numar de inmatriculare romanesc valid")
	if check_plate(text):
		print("Numarul de inmatriculare a fost gasit in baza de date")
	else:
		print("Numarul de inmatriculare nu a fost gasit in baza de date")
else:
	print("Nu s-a putut determina numarul de inmatriculare")
cv2.waitKey(0)
