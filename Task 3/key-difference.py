

keybefore = "220a6b8b954e2154743c7171658e2ac7a10d2c8c77823d715e70876b89a8612f"
keyafter  = "727fb9cf74e6633ae222bdb0508478153fcb3607a25422d5566f7ac2aadd5ce6"

count = 0

for index in range(0, len(keybefore)):
    if keybefore[index] != keyafter[index]:
        count+=1

print("Key Character Difference: ")
print(count)
