#ifndef STORY_ENGINE_H
#define STORY_ENGINE_H

/* 스토리 텍스트 파일을 한 글자씩 출력 (타이핑 효과)
 * path: 텍스트 파일 경로
 * delay_ms: 글자당 출력 딜레이 (밀리초, 기본 50ms 권장)
 * 반환: 성공 1, 실패 0
 */
int ShowStoryText(const char* path, int delay_ms);

/* 스토리 텍스트를 즉시 전체 출력 (스킵용)
 * path: 텍스트 파일 경로
 * 반환: 성공 1, 실패 0
 */
int ShowStoryTextInstant(const char* path);

#endif