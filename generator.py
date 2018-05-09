import random
import string
import argparse


parser = argparse.ArgumentParser(description='Generate random records')
parser.add_argument('--count', metavar='<count>', type=int, help='records count to generate')


RECORD_TEMPLATE = '<%%%%><{key}><{value}><$$$>'


def get_value_length_bytes(records_count):
    return 200 - len('<%%%%>') - len('<$$$>') - len('<<' + str(records_count) + '>>')


def generate_value(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))


def generate_records(count):
    value_lengths = range(1, get_value_length_bytes(count))

    keys = range(count)
    random.shuffle(keys)

    for key in keys:
        print RECORD_TEMPLATE.format(key=key, value=generate_value(random.choice(value_lengths)))


def get_records_count():
    args = parser.parse_args()

    return args.count


if __name__ == '__main__':
    generate_records(get_records_count())
