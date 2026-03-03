# sequence_id identifies one logical snapshot across all chunks.
uint32 sequence_id
# chunk_index is the zero-based chunk number in the snapshot.
uint32 chunk_index
# chunk_count is the total number of chunks in the snapshot.
uint32 chunk_count
# start_index is the global drone index of drones[0].
uint32 start_index
# valid_count is the number of valid entries contained in this chunk.
uint32 valid_count
# drones contains a chunk of the full drone state list.
hako_msgs/DroneVisualState[] drones
