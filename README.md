# 카드규칙
각 카드의 종류별로

spade A = s(1) ~ spade K = s(13)

diamond A = d(1)

heart A = h(1)

clover A = c(1)

# 보드규칙
board[10][20] 크기

board[0]~ 는 freecell을 나타냄

board[1]~ 는 homecell을 나타냄

board[2 ~ 9]~ 는 처음 카드가 나열된 보드를 나타냄

# 노드구조
node에는 위에 설명한 board[10][20]이 포함됨

알고리즘 적용을 위한 depth, hscore, fscore 등의 정수 값 존재

한 번에 이동 가능한 카드 수 계산을 위한 empty_freecell, empty_cell

퍼즐 해결 후 역추적하여 과정을 표기하기 위한 last_move, prev

퍼즐 해결 과정에서 다음 노드를 불러오기 위한 list_next

노드 리스트에 삽입시 동일한 fscore값을 가지는 노드를 스킵하기 위한 samefend

# list
리스트의 헤드에서 계속 노드를 꺼내와서 계산

# check_board
보드에 동일한 카드가 존재하는지, 부족한 카드 없이 모든 카드가 존재하는지 확인

# print_card
숫자를 인자로 받아 숫자에 해당하는 카드를 출력해주는 함수

# print_board
노드를 인자로 받아 해당 노드에 존재하는 board[10][20]을 출력해주는 함수

# find_top
보드와 라인 넘버를 인자로 받아 

해당 라인에 존재하는 가장 위에있는 카드의 종류와 동시에 움직일 수 있는 연결된 카드의 수를 반환해주는 함수

# find_move
노드를 인자로 받아 해당 노드에 존재하는 보드에서 이동 가능한 경우의 수를 출력해주는 함수

(이후 새로운 노드 생성시 사용)

# h_score
보드를 받아서 휴리스틱 스코어를 계산해 반환하는 함수

# initnode
보드의 초기 상태를 받아 새로운 노드로 만들어 반환하는 함수
