#pragma once

// Describes a sound's data format.
// NOTE: All sound data is assumed to be unsigned, thus minimum deflection is 0, not negative.
struct SoundFormat
{
    unsigned short num_channels;      // the number of channels per sample
    unsigned short bytes_per_channel; // i.e. 1 for 8 bits/channel, 2 for 16 bits/channel
    unsigned short samples_per_sec;   // in Hz.
    unsigned short bytes_per_sample;  // num_channels * bytes_per_channel.
};

// This declares the structure of the loaded sound data.
// NOTE: The 'samples' member points to a seperate buffer which holds the sound data.
// LoadWAV will automatically allocate this buffer from the heap. SaveWAV expects the buffer
// to be valid.
struct SoundFile
{
    SoundFormat format;      // format of the sound data.
    unsigned int loop_start; // start of the loop region, in samples
    unsigned int
        loop_end; // end of the loop region, in samples (inclusive of the last sample in the region, <= num_samples)
    unsigned int num_samples; // the count of samples in the file
    unsigned int length;      // length of the data in bytes == num_samples * format.bytes_per_sample
    unsigned int start_offset;
    char* samples; // sample data, length bytes long.
};
