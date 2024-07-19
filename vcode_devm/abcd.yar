rule signature_sample {
  meta:
    author = "Utsab Adhikari"
    description = "Detects malware exfiltrating contents of cosmo.jpeg"
    version = "0.2"
    date = "2024-07-10"
    reference = "Internal analysis"

  strings:
    $filename = "Desktop\\cosmo.jpeg"
    $language = "nim"
    $header = "content-Type"
    $base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
    $encoded_url = "@hwtwtwpw:w/w/whwewyw.wywowuwuwpw.wlwowcwawlw"

  condition:
    all of ($filename, $language, $header, $base64_chars, $encoded_url)
    
}
