#include <unity.h>
#include <hash_table.h>


void test_addTable(void) {
    Table *ht = ht_new();
    TEST_ASSERT_EQUAL_INT(1, ht_insert(ht, "Patel", "81"));
    TEST_ASSERT_EQUAL_INT(1, ht->count);
    //TEST_ASSERT_EQUAL("81", ht_search(ht, "Patel"));
    TEST_ASSERT_EQUAL_INT(1, ht_delete(ht, "Patel"));
    TEST_ASSERT_EQUAL_INT(0, ht->count);
    TEST_ASSERT_EQUAL(NULL, ht_search(ht, "Patel"));

}

void test_removeTable(void) {
    Table *ht = ht_new();
    TEST_ASSERT_EQUAL_INT(1, ht_insert(ht, "Patel", "81"));
    TEST_ASSERT_EQUAL_INT(1, ht_insert(ht, "Reed", "72"));
    TEST_ASSERT_EQUAL_INT(1, ht_insert(ht, "Vargas", "57"));
    TEST_ASSERT_EQUAL_INT(3, ht->count);
    TEST_ASSERT_EQUAL_INT(1, ht_delete(ht, "Patel"));
    TEST_ASSERT_EQUAL_INT(1, ht_delete(ht, "Reed"));
    TEST_ASSERT_EQUAL_INT(1, ht_delete(ht, "Vargas"));
    TEST_ASSERT_EQUAL_INT(1, ht_del_hash_table(ht));
}


int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_addTable);
    RUN_TEST(test_removeTable);

    return UNITY_END();
}
