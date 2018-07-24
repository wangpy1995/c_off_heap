//
// Created by wpy on 18-7-22.
//

#include <iostream>
#include "ArrowTest.h"

#include "arrow/io/api.h"
#include "arrow/ipc/api.h"
#include "arrow/api.h"

static arrow::MemoryPool *pool = arrow::default_memory_pool();

void TestReader(arrow::Table &table) {
    arrow::TableBatchReader tableBatchReader(table);
    int64_t num_rows = table.num_rows();
    int i, j;
    std::shared_ptr<arrow::RecordBatch> recordBatch;
    auto ids = std::static_pointer_cast<arrow::Int8Array>(table.column(0)->data()->chunk(0));
    auto comments = std::static_pointer_cast<arrow::BinaryArray>(table.column(1)->data()->chunk(0));
    auto comments_values = comments->value_data();
    const uint8_t *comments_ptr = comments_values->data() + comments->offset();
    for (i = 0; i < num_rows; ++i) {
        auto id = ids->Value(i);
        auto comment_first = comments->value_offset(i);
        auto comment_last = comments->value_offset(i + 1);
        std::vector<char> comment(comment_first, comment_last);
    }

}

int main() {
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
            str[j] = static_cast<char>(64 + i);
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

    TestReader(*(table.get()));

    return 0;


}