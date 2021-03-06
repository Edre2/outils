#########################################################################
# Fichier python avec des fonctions pour crypter / décrypter des textes #
# et d'autres fonctions (comme par exemple lister les nombres premiers) #
# Auteur : Edre                                                         #
#########################################################################

import math
import unidecode

ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


# Met toutes les lettres du texte en majuscules et enlève les accents et les
# espaces et la ponctuation
def removeAll(texte : str, to_remove: str):
    for suppr in to_remove:
        texte=texte.replace(suppr,"")
    return texte

def format(texte :str, remove=" ,;:!?.()[]{}-+=*\n"):
    return removeAll(unidecode.unidecode(texte).upper(),remove)

# Retourne la lettre la plus fréquente du texte
def plus_frequente(texte: str):
    dictionnaire={texte.count(i):i for i in ALPHABET}
    return dictionnaire[max(dictionnaire)]

def garderLettres(texte :str):
   text_final = ""
   for a in texte:
      if a.isalpha():
        text_final += a.upper()
   return text_final

# Une fonction qui crypte un texte avec le code de César en décalant les
# lettres de l'alphabet de n
def crypt_c(texte :str, n :int):
    texte = format(texte)
    texte_crypte = ""
    
    for lettre in texte:
        # Si c'est pas une lettre, on ignore
        if not lettre in ALPHABET:
            texte_crypte += lettre
        else:
            texte_crypte += chr((ord(lettre)+n-65) % 26 + 65)
    return texte_crypte

# Une fonction qui decrypte un texte avec le code de César en décalant les
# lettres de l'alphabet de n
def decrypt_c(texte :str, n :int):
    texte = format(texte)
    texte_decrypte = ""
    
    for lettre in texte:
        # Si c'est pas une lettre, on ignore
        if not lettre in ALPHABET:
            texte_decrypte += lettre
        else:
            texte_decrypte += chr((ord(lettre)-n-65) % 26 + 65)
    return texte_decrypte

# Décode automatiquement un code césar
def decodage_automatique_c(texte :str):
    return decrypt_c(texte, (plus_frequente(format(texte))-65-4)%26)

# Une fonction qui crypte un texte avec le code Vigenère et le mot
def crypt_v(texte :str, mot :str):
    texte = format(texte)
    texte_crypte = ""
    
    for i in range(len(texte)):
        if not texte[i] in ALPHABET:
            texte_crypte += texte[i]
        else:
            texte_crypte += chr((ord(texte[i].upper()) + ord(mot[i%len(mot)].upper()) - 65 - 65) % 26 + 65)
    
    return texte_crypte

# Une fonction qui crypte un texte avec le code Vigenère et le mot
def decrypt_v(texte :str, mot :str):
    texte = format(texte)
    texte_decrypte = ""
    
    for i in range(len(texte)):
        if not texte[i] in ALPHABET:
            texte_decrypte += texte[i]
        else:
            texte_decrypte += chr((ord(texte[i].upper()) - ord(mot[i%len(mot)].upper())) % 26 + 65)
    
    return texte_decrypte

# Une fonciton qui décrypte automatiquement un message chiffré avec vigenère
# def decodage_automatique_v(texte :str, TAILLE_MAX = 20, FREG_MIN = 10):
def decodage_automatique_v(texte :str, TAILLE_MAX = 20):
   texte2 = texte
   texte = garderLettres(texte)

   mots_possibles = []
   for a in range(26):
      mots_possibles.append("")

   # probable = []
   # for a in range(26):
   #    probable.append(True)

   freq_e_min = [0]
   for a in range(TAILLE_MAX-1):
      freq_e_min.append(100)

   longueur = len(texte)

   for i in range(TAILLE_MAX):
      for j in range(i):
         count = []
         for a in range(26):
            count.append(0)

         a = 0
         while i*a+j < longueur:
             count[ord(texte[i*a+j]) - ord('A')] += 1
             a += 1

         tot = 0
         count_max = max(count)
         count_max_pos = count.index(count_max)

         for a in range(26):
            tot += count[a]
         
         freq_max = count_max / tot * 100

         if freq_max < freq_e_min[i]:
            freq_e_min[i] = freq_max

         # if freq_max < FREG_MIN:
         #    probable[i] = False

         mots_possibles[i] += chr((count_max_pos - 4 + 26) % 26 + ord('A'))

   # mots_probables = []
   
   # for i in range(TAILLE_MAX):
   #    if probable[i]:
   #       mots_probables.append(mots_possibles[i])

   for i in range(1, TAILLE_MAX):
      print(mots_possibles[i], " : ", freq_e_min[i])
      print(decrypt_v(texte2, mots_possibles[i]))
      print()

   # return mots_probables
   return mots_possibles[freq_e_min.index(max(freq_e_min))]
         
# A function that returns if a number is a prime number or not
def isprime(nb :int):
    if nb <= 3:
        return nb > 1
    if nb % 2 == 0 or nb % 3 == 0:
        return False

    sqrt_nb = math.ceil(math.sqrt(nb))
    # Les nombres premiers sont de la forme 6k+1 ou 6k-1
    # Preuve :
    # Si n % 6 = 1, alors n peut être premier
    # Si n % 6 = 0, 2, 4, alors 2 | n
    # Si n % 6 = 3, alors 3 | n
    # Si n % 6 = 5 = -1, alors n peut être premier

    # on peut ne tester que les nombres premiers <= à sqrt_n
    # (on en teste même un peu plus mais bon...)

    for i in range(5, sqrt_nb, 6):
        if nb % i == 0 or nb % (i +2) == 0:
            return False
    
    return True

# A function that returns the prime numbers until 2 000 000 by reading a file
# that already has them
def primeNbs():
    input_file = open("../intPrimeTo2000000.txt", "r")
    with open(input_file,"r") as f:
        nbsPrems=list(map(int,f.read().split("\n")))
    return nbsPrems

# A function that returns the prime factors of an integer using a file with the
# prime numbers until 2 000 000 to be faster by not testing not prime numbers
def primeFacts(nb :int):
    factprems = []
    #primeNbs = primeNbs()
    i = 2
    while nb > 1:
        while nb % i == 0:
            nb = nb / i
            factprems.append(i)
        i += 1
    return factprems

# Retourne les nombres premiers jusqu'à n
def NbsPremsjusquaN(n :int):
    if n <= 0:
        return 0
    if n == 1:
        return [2]
    nbsPrems = [2,3]

    for i in range(5,n,6):
        for j in nbsPrems:
            if i%j==0:
                break
        else:
            nbsPrems.append(i)
        for j in nbsPrems:
            if (i+2)%j==0:
                break
        else:
            nbsPrems.append(i+2)
    return nbsPrems
