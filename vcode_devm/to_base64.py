def hex_to_base64(hex_string):
   
    binary_string = ""
    for i in range(0, len(hex_string), 2):
        binary_string += bin(int(hex_string[i:i+2], 16))[2:].zfill(8)
 
    base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    base64_string = ""
    padding = 0
 
  
    for i in range(0, len(binary_string), 6):
        if i + 6 > len(binary_string):
            padding = 6 - (len(binary_string) - i)
            binary_chunk = binary_string[i:] + '0' * padding
        else:
            binary_chunk = binary_string[i:i+6]
        base64_string += base64_chars[int(binary_chunk, 2)]
 

    if padding:
        base64_string += "=" * (padding // 2)
 
    return base64_string
 

hex_string = input("please Enter the input in hex: ") 
base64_string = hex_to_base64(hex_string)
print(base64_string)