//
// Created by wpy on 18-7-22.
//

#include "ArrowTest.h"

#include "arrow/io/api.h"
#include "arrow/ipc/api.h"
#include "arrow/api.h"

int main() {
    arrow::MemoryPool *pool = arrow::default_memory_pool();

    arrow::Int8Builder int8Builder;
    int i;
    for (i = 1; i <= 9; ++i) {
        int8Builder.Append(i);
    }
    std::shared_ptr<arrow::Array> id_array;
    int8Builder.Finish(&id_array);

    arrow::BinaryBuilder binaryBuilder;
    char str[6] = {0};
    int j;
    for (i = 1; i <= 9; ++i) {
        for (j = 0; j < 6; ++j) {
            str[j] = static_cast<char>(random());
        }
        binaryBuilder.Append(str);
    }
    std::shared_ptr<arrow::Array> comment_array;
    binaryBuilder.Finish(&comment_array);

    auto poolBuffer = std::make_shared<arrow::PoolBuffer>(pool);
    arrow::io::BufferOutputStream bufferOutputStream(poolBuffer);

    std::vector<std::shared_ptr<arrow::Field>> schema_vector = {
            arrow::field("id", arrow::int64()),
            arrow::field("comment", arrow::binary())
    };
    auto const schema = std::make_shared<arrow::Schema>(schema_vector);
    std::shared_ptr<arrow::ipc::RecordBatchWriter> writer;
    arrow::ipc::RecordBatchStreamWriter::Open(&bufferOutputStream, schema, &writer);

    std::shared_ptr<arrow::Table> table;
    arrow::MakeTable(schema, {id_array, comment_array}, &table);
    writer.get()->WriteTable(*(table.get()));
    writer.get()->Close();

    return 0;


}