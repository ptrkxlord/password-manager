import json
import os
import base64
from urllib.parse import urlparse

def extract_har(har_path, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    with open(har_path, 'r', encoding='utf-8') as f:
        har_data = json.load(f)

    for entry in har_data['log']['entries']:
        request = entry['request']
        response = entry['response']
        url = request['url']
        
        # Parse URL to get path
        parsed_url = urlparse(url)
        path = parsed_url.path
        if not path or path == '/':
            path = '/index.html'
        
        # Determine file path
        # Remove leading slash and join with output_dir
        file_path = os.path.join(output_dir, path.lstrip('/'))
        
        # Create directories if they don't exist
        os.makedirs(os.path.dirname(file_path), exist_ok=True)

        content = response.get('content', {})
        text = content.get('text')
        encoding = content.get('encoding')

        if text:
            try:
                if encoding == 'base64':
                    with open(file_path, 'wb') as f:
                        f.write(base64.b64decode(text))
                else:
                    with open(file_path, 'w', encoding='utf-8') as f:
                        f.write(text)
                print(f"Extracted: {url} -> {file_path}")
            except Exception as e:
                print(f"Failed to extract {url}: {e}")

if __name__ == "__main__":
    HAR_PATH = r'c:\Users\zxc23\OneDrive\Desktop\d\antigravity.google.har'
    OUTPUT_DIR = r'c:\Users\zxc23\OneDrive\Desktop\d\extracted_assets'
    extract_har(HAR_PATH, OUTPUT_DIR)
