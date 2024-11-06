void kernel_entry()
{
    // Get the VGA Video Memory Base Address
    char* video_memory = (char*) 0xB8000;

    // Replace the first character with 'X'
    *video_memory = 'X';
}