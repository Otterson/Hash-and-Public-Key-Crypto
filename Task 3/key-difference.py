

keybefore = "4d9de24b2617e3903c72b44e65e733bf"
keyafter  = "9fbc69af901b178f9f3af22b5f45f781"

count = 0

for index in range(0, len(keybefore)):
    if keybefore[index] != keyafter[index]:
        count+=1

print("Key Character Difference: ")
print(count)
